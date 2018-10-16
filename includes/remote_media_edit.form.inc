<?php
/**
 * @file
 * Remote media OBJ editing form.
 */
/**
 * Retrives the OBJ edit form.
 *
 * @param AbstractObject $object
 *   The Islandora object.
 *
 * @return array
 *   The form array.
 */
function islandora_remote_media_edit_obj(AbstractObject $object) {
  return drupal_get_form('islandora_remote_media_edit_obj_form', $object);
}
/**
 * Form callback.
 */
function islandora_remote_media_edit_obj_form($form, &$form_state, AbstractObject $object) {
  $content = $object['OBJ']->content;
  return array(
    'content' => array(
      '#title' => t('Embed code'),
      '#type' => 'textarea',
      '#description' => t('Embed code for the remote media.'),
      '#default_value' => $content,
    ),
    'object' => array(
      '#type' => 'value',
      '#value' => $object->id,
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
    'cancel' => array(
      '#markup' => l('Cancel', url('islandora/object/' . $object->id)),
    ),
  );
}
/**
 * From submit function.
 */
function islandora_remote_media_edit_obj_form_submit($form, &$form_state) {
  $object = islandora_object_load($form_state['values']['object']);
  if (!$object['OBJ']) {
    $content = $object->constructDatastream('OBJ', 'M');
    $content->mimetype = 'text/plain';
    $content->label = 'Embed code';
  }
  else {
    $content = $object['OBJ'];
  }
  $content->setContentFromString($form_state['values']['content']);
  drupal_set_message(t("Embed code updated for !object.", array('!object' => $object->id)));
  drupal_goto("islandora/object/{$object->id}/manage/datastreams");
}
