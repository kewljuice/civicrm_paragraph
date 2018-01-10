<?php

/**
 * Create a paragraph bundle.
 *
 * @param $machine
 * @param $label
 */
function _civicrm_paragraph_bundle_install($machine, $label) {
  # https://drupal.stackexchange.com/questions/164342/create-entity-bundles-programmatically
  # TODO check for existing bundle.
  $bundle = new stdClass();
  $bundle->name = $label; # user friendly label.
  $bundle->bundle = $machine; # machine name.
  $bundle->locked = 0;
  try {
    paragraphs_bundle_save($bundle);
  } catch (Exception $e) {
    watchdog('_civicrm_paragraph_bundle_install', $e->getMessage());
  }
}

/**
 * Delete a paragraph bundle.
 *
 * @param $machine
 */
function _civicrm_paragraph_bundle_uninstall($machine) {
  paragraphs_bundle_delete($machine);
}

/**
 * Create a variable.
 *
 * @param $machine
 * @param $value
 */
function _civicrm_paragraph_variable_create($machine, $value) {
  variable_set($machine, $value);
}

/**
 * Delete a variable.
 *
 * @param $machine
 */
function _civicrm_paragraph_variable_delete($machine) {
  variable_del($machine);
}

/**
 * Create a list field.
 *
 * @param $field
 * @param $label
 */
function _civicrm_paragraph_field_list_create($field, $label) {
  # Define field.
  $field = [
    'field_name' => $field,
    'label' => $label,
    'type' => 'list_integer',
    'cardinality' => FIELD_CARDINALITY_UNLIMITED, # Allow multiple values!
  ];
  # Check if field exists, else create our field.
  try {
    field_create_field($field);
  } catch (Exception $e) {
    watchdog('_civicrm_paragraph_field_list_create', $e->getMessage());
  }
}

/**
 * Create a contact field.
 *
 * @param $field
 * @param $label
 */
function _civicrm_paragraph_field_contact_create($field, $label) {
  # Define field.
  $field = [
    'field_name' => $field,
    'label' => $label,
    'type' => 'civicrm_contact_ref_contact',
  ];
  # Check if field exists, else create our field.
  try {
    field_create_field($field);
  } catch (Exception $e) {
    watchdog('_civicrm_paragraph_field_contact_create', $e->getMessage());
  }
}

/**
 * Add a field to entity - bundle.
 *
 * @param $entity
 * @param $field
 * @param $bundle
 * @param $label
 * @param $description
 * @param $widget
 */
function _civicrm_paragraph_field_append($entity, $field, $bundle, $label, $description, $widget) {
  $instance = [
    'field_name' => $field,
    'entity_type' => $entity,
    'bundle' => $bundle,
    'label' => $label,
    'description' => $description,
    'widget' => [
      'type' => $widget,
    ],
    'options' => [
      NULL => '',
      'info' => 'info',
      'success' => 'success',
      'warning' => 'warning',
      'error' => 'error',
    ],
    'display' => [
      'default' => [
        'label' => 'hidden',
        'type' => 'hidden',
      ],
    ],
    'required' => FALSE,
  ];
  try {
    field_create_instance($instance);
  } catch (Exception $e) {
    watchdog('_civicrm_paragraph_field_append', $e->getMessage());
  }
}

/**
 * Detach a field from entity - bundle.
 *
 * @param $entity
 * @param $field
 * @param $bundle
 */
function _civicrm_paragraph_field_detach($entity, $field, $bundle) {
  # https://api.drupal.org/api/drupal/modules%21field%21field.crud.inc/function/field_delete_instance/7.x
  if ($instance = field_info_instance($entity, $field, $bundle)) {
    field_delete_instance($instance, FALSE); # FALSE: disable if the last instance/object of this field had been deleted.
  }
}

/**
 * Delete a field.
 *
 * @param $field
 */
function _civicrm_paragraph_field_delete($field) {
  field_delete_field($field);
}
