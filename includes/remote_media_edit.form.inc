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

  $html = check_markup($form_state['values']['content'], "full_html");
  // Strip script tags from datastream
  $doc = new DOMDocument();
  // load the HTML string we want to strip
  $doc->loadHTML($html);

  // get all the script tags
  $script_tags = $doc->getElementsByTagName('script');

  $length = $script_tags->length;

  // for each tag, remove it from the DOM
  for ($i = 0; $i < $length; $i++) {
    $script_tags->item($i)->parentNode->removeChild($script_tags->item($i));
  }

  // get the HTML string back
  $no_script_html_string = $doc->saveHTML();

//  $content->setContentFromString(check_markup($form_state['values']['content'], "full_html"));

  $content->setContentFromString(check_markup($no_script_html_string, "full_html"));
  
  drupal_set_message(t("Embed code updated for !object.", array('!object' => $object->id)));
  drupal_goto("islandora/object/{$object->id}/manage/datastreams");
}
