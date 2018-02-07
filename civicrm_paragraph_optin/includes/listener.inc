<?php

/**
 * Custom 'listener' function to render paragraph specific content.
 *
 * @param $output
 * @param $object
 *
 * @return string
 */
function _civicrm_optin_render($output, $object) {
  # Output
  $output = NULL;
  # Check if user is anonymous.
  if (user_is_anonymous()) {
    # Fetch opt-in form.
    $output = [
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => theme('civicrm_paragraph_optin_anom', ['object' => $object]),
      '#attributes' => [
        'class' => ['civicrm_paragraph_optin'],
        'id' => 'civicrm_paragraph_optin',
      ],
      '#attached' => [
        'css' => [
          drupal_get_path('module', 'civicrm_paragraph_optin') . '/css/civicrm_paragraph_optin.css',
        ],
      ],
    ];
  }
  else {
    # Fetch alter subscriptions form.
    $output = [
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => theme('civicrm_paragraph_optin_auth', ['object' => $object]),
      '#attributes' => [
        'class' => ['civicrm_paragraph_optin'],
        'id' => 'civicrm_paragraph_optin',
      ],
      '#attached' => [
        'css' => [
          drupal_get_path('module', 'civicrm_paragraph_optin') . '/css/civicrm_paragraph_optin.css',
        ],
      ],
    ];
  }
  # Render & return output.
  return drupal_render($output);
}

/**
 * Custom 'listener' function for paragraph specific settings.
 *
 * @param $element
 * @param $form_state
 * @param $context
 */
function civicrm_paragraph_civicrm_optin(&$element, &$form_state, &$context) {
  # Build options array.
  $options = variable_get('civicrm_paragraph_optin');
  $param = [];
  foreach ($options as $key => $option) {
    # Only show active choices.
    if ($option['is_active']) {
      $param[$key] = $option['label'];
    }
  }
  # Fetch default value.
  $default = [];
  foreach ($context['items'] as $result) {
    array_push($default, $result['value']);
  }
  $element['#type'] = 'checkboxes';
  $element['#options'] = $param;
  $element['#default_value'] = $default;
}
