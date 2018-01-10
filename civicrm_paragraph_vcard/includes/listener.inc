<?php

/**
 * Custom 'listener' function to render paragraph specific content.
 *
 * @param $output
 * @param $object
 *
 * @return string
 */
function _civicrm_vcard_render($output, $object) {
  # Display according to settings.
  $output = NULL;
  $cid = NULL;
  # Define civicrm contact_id.
  $contact = field_get_items('paragraphs_item', $object['#entity'], 'civicrm_paragraph_contact');
  if ($contact[0]) {
    # Use contact_id set by field 'civicrm_paragraph_contact'.
    $cid = $contact[0]['contact_id'];
  }
  else {
    # Use logged in user as default.
    try {
      civicrm_initialize();
      $user_contact = civicrm_api3('Contact', 'getSingle', [
        'sequential' => 1,
        'return' => ["contact_id"],
        'id' => "user_contact_id",
      ]);
    } catch (Exception $e) {
      // watchdog('_civicrm_vcard_render', $e->getMessage());
    }
    if ($user_contact['contact_id']) {
      $cid = $user_contact['contact_id'];
    }
  }
  # Continue when cid is set.
  if ($cid) {
    $settings = field_get_items('paragraphs_item', $object['#entity'], 'civicrm_paragraph_settings');
    switch ($settings[0]['value']) {
      case 2:
        # With Caching.
        $layout2 = &drupal_static(__FUNCTION__);
        if (!isset($layout2)) {
          if ($cache = cache_get('civicrm_paragraph_vcard_layout2')) {
            $layout2 = $cache->data;
          }
          else {
            $layout2 = _civicrm_vcard_render_layout2($cid);
            cache_set('civicrm_paragraph_vcard_layout2', $layout2, 'cache');
          }
        }
        $output = $layout2;
        break;
      default:
        # With Caching.
        $layout1 = &drupal_static(__FUNCTION__);
        if (!isset($layout1)) {
          if ($cache = cache_get('civicrm_paragraph_vcard_layout1')) {
            $layout1 = $cache->data;
          }
          else {
            $layout1 = _civicrm_vcard_render_layout1($cid);
            cache_set('civicrm_paragraph_vcard_layout1', $layout1, 'cache');
          }
        }
        $output = $layout1;
        break;
    }
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
function civicrm_paragraph_civicrm_vcard(&$element, &$form_state, &$context) {
  # Build options array.
  $options = variable_get('civicrm_paragraph_vcard');
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

/*
 * Display vCard layout 1.
 *
 * @return String
 */
function _civicrm_vcard_render_layout1($cid) {
  # Fetch contact variables.
  try {
    civicrm_initialize();
    $contact = civicrm_api3('Contact', 'getSingle', [
      'sequential' => 1,
      'id' => 1,
    ]);
  } catch (Exception $e) {
    watchdog('_civicrm_vcard_render_layout1', $e->getMessage());
  }
  # Generate table.
  $table = [
    '#theme' => 'table',
    '#rows' => [
      [t('name'), $contact['first_name'] . " " . $contact['last_name']],
      [t('email'), $contact['email']],
      [t('type'), $contact['contact_type']],
    ],
  ];
  # Generate output.
  $output = [
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => drupal_render($table),
    '#attributes' => [
      'class' => ['civicrm_paragraph_vcard_layout1'],
      'id' => 'civicrm-paragraph-vcard-layout1',
    ],
  ];
  return $output;
}

/*
 * Display vCard layout 2.
 *
 * @return String
 */
function _civicrm_vcard_render_layout2($cid) {
  # Fetch contact variables.
  try {
    civicrm_initialize();
    $contact = civicrm_api3('Contact', 'getSingle', [
      'sequential' => 1,
      'id' => 1,
    ]);
  } catch (Exception $e) {
    watchdog('_civicrm_vcard_render_layout2', $e->getMessage());
  }
  # Generate table.
  $table = [
    '#theme' => 'table',
    '#rows' => [
      [t('type'), $contact['contact_type']],
      [t('name'), $contact['first_name'] . " " . $contact['last_name']],
      [t('email'), $contact['email']],
      [t('street'), $contact['street_address']],
      [t('city'), $contact['postal_code'] . " " . $contact['city']],
    ],
  ];
  # Generate output.
  $output = [
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => drupal_render($table),
    '#attributes' => [
      'class' => ['civicrm_paragraph_vcard_layout2'],
      'id' => 'civicrm-paragraph-vcard-layout2',
    ],
  ];
  return $output;
}
