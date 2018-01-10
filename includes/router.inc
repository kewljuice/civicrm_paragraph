<?php

/**
 * Implement hook_entity_view_alter().
 */
function civicrm_paragraph_entity_view_alter(&$build, $type) {
  # Custom router to 'listener' functions to get paragraph specific content.
  if ($build['#entity_type'] == 'paragraphs_item' && 0 === strpos($build['#bundle'], 'civicrm_')) {
    # Change its weight.
    $build[$build['#bundle']]['#weight'] = -10;
    # Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = '_' . $build['#bundle'] . '_render';
  }
}

/**
 * Implement hook_field_widget_form_alter().
 */
function civicrm_paragraph_field_widget_form_alter(&$element, &$form_state, $context) {
  # Custom router to 'listener' functions to get paragraph specific options.
  if (!empty($element['#entity_type']) && $element['#entity_type'] == 'paragraphs_item' && $element['#field_name'] == 'civicrm_paragraph_settings') {
    switch ($element['#bundle']) {
      default:
        # https://www.drupal.org/docs/7/creating-custom-modules/creating-drupal-7-hooks
        # Routing to listener.
        foreach (module_implements($element['#bundle']) as $module) {
          $function = $module . '_' . $element['#bundle'];
          # Execute listener function.
          $function($element, $form_state, $context);
        }
        break;
    }
  }
}
