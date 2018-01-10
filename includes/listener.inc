<?php

/**
 * Custom 'listener' function to render paragraph specific content.
 *
 * @param $output
 * @param $object
 *
 * @return string
 */
function _civicrm_hello_render($output, $object) {
  # Fetch properties from our user.
  try {
    civicrm_initialize();
    $contact = civicrm_api3('Contact', 'get', [
      'sequential' => 1,
      'return' => ["first_name", "last_name"],
      'id' => "user_contact_id",
    ]);
  } catch (Exception $e) {
    // watchdog('_civicrm_hello_render', $e->getMessage());
  }
  # Display if properties exists.
  if (isset($contact['values'][0]['contact_id'])) {
    # Display according to settings.
    $firstname = $contact['values'][0]['first_name'];
    $lastname = $contact['values'][0]['last_name'];
    $settings = field_get_items('paragraphs_item', $object['#entity'], 'civicrm_paragraph_settings');
    switch ($settings[0]['value']) {
      case 2:
        $name = $lastname;
        break;
      case 3:
        $name = $firstname . ", " . $lastname;
        break;
      case 4:
        $name = $lastname . ", " . $firstname;
        break;
      default:
        $name = $firstname;
        break;
    }
  }
  # Generate output.
  $output = [
    '#type' => 'container',
    '#attributes' => [
      'class' => ['civicrm-paragraph-hello'],
    ],
    'span' => [
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => t('Hello') . ' ' . $name,
      '#attributes' => [
        'class' => ['civicrm-paragraph-hello-content'],
      ],
    ],
  ];
  # Render and return output.
  return drupal_render($output);
}

/**
 * Custom 'listener' function for paragraph specific settings.
 *
 * @param $element
 * @param $form_state
 * @param $context
 */
function civicrm_paragraph_civicrm_hello(&$element, &$form_state, &$context) {
  # Build options array.
  $options = variable_get('civicrm_paragraph_hello');
  $param = [];
  foreach ($options as $key => $option) {
    $param[$key] = $option['label'];
  }
  # Fetch default value.
  $default = 0;
  if (isset($context['items'][0]['value'])) {
    $default = $context['items'][0]['value'];
  }
  $element['#type'] = 'radios';
  $element['#options'] = $param;
  $element['#default_value'] = $default;
}
