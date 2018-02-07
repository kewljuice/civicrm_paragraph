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
    # TODO: form for anonymous with check for anonymous groups!
    # Display output.
    $output = [
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => "Opt-in: anonymous",
      '#attributes' => [
        'class' => ['civicrm_paragraph_optin'],
        'id' => 'civicrm-paragraph-vcard-optin',
      ],
    ];
  }
  else {
    # Fetch opt-in form.
    $output = drupal_get_form('civicrm_paragraph_optin_form', $object);
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
