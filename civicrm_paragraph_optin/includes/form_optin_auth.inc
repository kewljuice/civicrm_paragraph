<?php

/**
 *  Form constructor for the paragraph opt-in form.
 */
function civicrm_paragraph_optin_auth_form($form, &$form_state, $object) {
  # Fetch contact from CiviCRM API.
  try {
    civicrm_initialize();
    $user_contact = civicrm_api3('Contact', 'getSingle', [
      'sequential' => 1,
      'return' => ["contact_id"],
      'id' => "user_contact_id",
    ]);
  } catch (Exception $e) {
    // watchdog('_civicrm_paragraphs', $e->getMessage());
  }
  # Check if user has CiviCRM contact id.
  if ($user_contact['contact_id']) {
    # Fetch items from variable.
    $list = variable_get('civicrm_paragraph_optin');
    # Fetch entity choices from field settings.
    $newsletters = [];
    foreach ($object['#entity']->civicrm_paragraph_settings['und'] as $setting) {
      $searchid = $setting['value'];
      $label = $list[$setting['value']]['label'];
      # The options to display in our checkboxes.
      $newsletters[$searchid] = $label;
    }
    # Fetch default values from CiviCRM API.
    try {
      $groups = civicrm_api3('GroupContact', 'get', [
        'sequential' => 1,
        'return' => ["group_id"],
        'contact_id' => "user_contact_id",
      ]);
    } catch (Exception $e) {
      // watchdog('_civicrm_paragraphs', $e->getMessage());
    }
    $default = [];
    foreach ($groups['values'] as $group) {
      $default[] = $group['group_id'];
    }
    # The drupal checkboxes form field definition.
    $form['subscriptions'] = [
      '#type' => 'checkboxes',
      '#description' => t('Select the newsletter(s) you would like to subscribe to.'),
      '#options' => $newsletters,
      '#ajax' => [
        'callback' => 'civicrm_paragraph_optin_auth_ajax',
        'wrapper' => 'subscriptions',
      ],
      '#default_value' => $default,
      '#prefix' => '<div id="subscriptions">',
      '#suffix' => '</div>',
    ];
    # Provide a submit button.
    /*
      $form['submit'] = [
      '#type' => 'submit',
      '#value' => 'Update',
      ];
     */
  }
  else {
    $form = NULL;
  }
  # return form.
  return $form;
}

/**
 *  Form ajax submit for the paragraph opt-in form.
 */
function civicrm_paragraph_optin_auth_ajax(&$form, &$form_state) {
  # Update opt-in(s).
  foreach ($form['subscriptions']['#options'] as $key => $value) {
    if ($form['subscriptions'][$key]['#value']) {
      $params = [
        'group_id' => $key,
        'contact_id' => 'user_contact_id',
        'status' => 'Added',
      ];
    }
    else {
      $params = [
        'group_id' => $key,
        'contact_id' => 'user_contact_id',
        'status' => 'Removed',
      ];
    }
    # Save params to CiviCRM API.
    try {
      $result = civicrm_api3('GroupContact', 'create', $params);
    } Catch (Exception $e) {
      watchdog('civicrm_paragraph_optin_ajax', $e->getMessage());
    }
  }
  # Return form.
  return $form;
}
