<?php

/**
 * Implements hook_menu().
 */
function civicrm_paragraph_optin_menu() {
  $items = [];
  $items['admin/config/content/civicrm_paragraph/optin'] = [
    'title' => 'CiviCRM paragraph: Opt-in Settings',
    'description' => "Configuration for CiviCRM 'Opt-in' paragraph",
    'page callback' => 'drupal_get_form',
    'page arguments' => ['civicrm_paragraph_optin_admin_form'],
    'access arguments' => ['access administration pages'],
    'type' => MENU_NORMAL_ITEM,
  ];
  return $items;
}

/**
 * Custom form.
 */
function civicrm_paragraph_optin_admin_form($form, &$form_state) {
  # Markup
  $form['help'] = [
    '#type' => 'fieldset',
    '#title' => t('Help'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];
  $form['help']['text'] = [
    '#markup' => "Here you can:<br>- change group labels (label)<br>- activate groups (is_active) for use in paragraphs<br>- define on which groups anonymous users will be registered (anonymous) ",
  ];
  # Fieldset.
  $form['items'] = [
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];
  # Fetch & loop options.
  $options = variable_get('civicrm_paragraph_optin');
  # Check for options via CiviCRM API.
  $options = civicrm_paragraph_optin_update_list($options);
  # Fetch & loop options.
  foreach ($options as $key => $value) {
    $form['items'][$key] = [
      '#type' => 'fieldset',
      '#title' => $value['machine_name'],
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    ];
    # Set tree=true for passing arrays.
    $form['items']['#tree'] = TRUE;
    # Add id.
    $form['items'][$key]['id'] = [
      '#type' => 'hidden',
      '#default_value' => $key,
      '#attributes' => ['readonly' => 'readonly'],
    ];
    # Add machine_name.
    $form['items'][$key]['machine_name'] = [
      '#type' => 'hidden',
      '#default_value' => $value['machine_name'],
      '#attributes' => ['readonly' => 'readonly'],
    ];
    # Add label.
    $form['items'][$key]['label'] = [
      '#type' => 'textfield',
      '#title' => t('label'),
      '#default_value' => $value['label'],
    ];
    # Add is_active.
    $form['items'][$key]['is_active'] = [
      '#type' => 'checkbox',
      '#title' => t('is_active'),
      '#default_value' => $value['is_active'],
    ];
    # Add anonymous.
    $form['items'][$key]['anonymous'] = [
      '#type' => 'checkbox',
      '#title' => t('anonymous'),
      '#default_value' => $value['anonymous'],
    ];
  }
  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Submit',
  ];
  return $form;
}

/**
 * Custom form submit.
 */
function civicrm_paragraph_optin_admin_form_submit($form, &$form_state) {
  # Loop our result 'items'.
  $options = variable_get('civicrm_paragraph_optin');
  foreach ($form_state['values']['items'] as $value) {
    $options[$value['id']]['machine_name'] = $value['machine_name'];
    $options[$value['id']]['label'] = $value['label'];
    $options[$value['id']]['is_active'] = $value['is_active'];
    $options[$value['id']]['anonymous'] = $value['anonymous'];
  }
  # Save options.
  variable_set('civicrm_paragraph_optin', $options);
  drupal_set_message(t('The form has been submitted.'));
}

/**
 * Custom function to update opt-in list.
 */
function civicrm_paragraph_optin_update_list($options) {
  # Fetch opt-in properties form CiviCRM API.
  try {
    civicrm_initialize();
    $result = civicrm_api3('Group', 'get', [
      'sequential' => 1,
      'return' => ['id', 'name', 'title'],
      'group_type' => 'Mailing List',
      'is_active' => 1,
    ]);
  } catch (Exception $e) {
    watchdog('civicrm_paragraph_optin_update_list', $e->getMessage());
  }
  # Loop opt-in properties.
  foreach ($result['values'] as $value) {
    # Check if item exists.
    if (!array_key_exists($value['id'], $options)) {
      # Add new opt-in properties.
      $options[$value['id']] = [
        'machine_name' => $value['name'],
        'label' => $value['title'],
        'is_active' => FALSE,
        'anonymous' => FALSE,
      ];
    }
  }
  # Save options.
  variable_set('civicrm_paragraph_optin', $options);
  # Return options.
  return $options;
}
