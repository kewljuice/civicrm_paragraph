<?php

/**
 * Implements hook_theme().
 */
function civicrm_paragraph_optin_theme($existing, $type, $theme, $path) {
  return [
    'civicrm_paragraph_optin_auth' => [
      'variables' => [
        'object' => [],
      ],
      'template' => 'templates/civicrm_paragraph_optin_auth',
    ],
  ];
}
