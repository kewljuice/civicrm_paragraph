<?php

/**
 *  Form constructor for the paragraph opt-in form.
 */
function civicrm_paragraph_optin_anom_form($form, &$form_state, $object) {
  # Contact Email address
  $form['email'] = [
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#required' => TRUE,
    '#description' => "Please enter your email.",
    '#size' => 20,
    '#element_validate' => ['civicrm_paragraph_optin_anom_form_validate_email'],
  ];
  # Provide a submit button.
  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Subscribe'),
  ];
  # return form.
  return $form;
}

/**
 *  Form validate for the paragraph opt-in form.
 */
function civicrm_paragraph_optin_anom_form_validate_email($element, &$form_state, $form) {
  if (!valid_email_address($element['#value'])) {
    form_error($element, t('Please enter a valid email address.'));
  }
}

/**
 *  Form submit for the paragraph opt-in form.
 */
function civicrm_paragraph_optin_anom_form_submit(&$form, &$form_state) {
  # Insert contact.
  $email = $form_state['values']['email'];
  try {
    $contact = civicrm_api3('Contact', 'create', [
      'contact_type' => 'Individual',
      'source' => 'Newsletter subscription',
      'email' => $email,
    ]);
  } catch (Exception $e) {
    watchdog('civicrm_paragraph_optin_anom_form_submit', $e->getMessage());
  }
  $contact_id = $contact['id'];
  # Fetch and save anonymous groups.
  $list = variable_get('civicrm_paragraph_optin');
  foreach ($list as $key => $value) {
    if ($value['anonymous']) {
      $params = [
        'group_id' => $key,
        'contact_id' => $contact_id,
        'status' => 'Added',
      ];
      # Save params to CiviCRM API.
      try {
        $result = civicrm_api3('GroupContact', 'create', $params);
      } Catch (Exception $e) {
        watchdog('civicrm_paragraph_optin_anom_form_submit', $e->getMessage());
      }
    }
  }
  # Message.
  drupal_set_message(t('The form has been submitted.'));
  # Return form.
  return $form;
}
