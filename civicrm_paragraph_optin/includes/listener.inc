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
  # Display according to settings.
  $output = NULL;
  $output = [
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => "Opt-in",
    '#attributes' => [
      'class' => ['civicrm_paragraph_optin'],
      'id' => 'civicrm-paragraph-vcard-optin',
    ],
  ];
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