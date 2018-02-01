<?php

/**
 * Implements hook_theme().
 */
function civicrm_paragraph_vcard_theme($existing, $type, $theme, $path) {
  return array(
    'civicrm_paragraph_vcard_layout1' => array(
      'variables' => array(
        'contact' => array(),
      ),
      'template' => 'templates/civicrm-paragraph-vcard-layout1'
    ),
    'civicrm_paragraph_vcard_layout2' => array(
      'variables' => array(
        'contact' => array(),
      ),
      'template' => 'templates/civicrm-paragraph-vcard-layout2'
    ),
  );
}
