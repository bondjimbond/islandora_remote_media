<?php

/**
 * @file
 * Theme hooks.
 */

/**
 * Implements hook_preprocess().
 */
function islandora_remote_media_preprocess_islandora_remote_media(array &$variables) {
  module_load_include('inc', 'islandora', 'includes/datastream');
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/solution_packs');
  module_load_include('inc', 'islandora', 'includes/authtokens');
  module_load_include('inc', 'islandora', 'includes/metadata');
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');
  $object = $variables['object'];
  $repository = $object->repository;
  // We should eventually remove the DC object and dc_array code as it only
  // exists to not break legacy implementations.
  $variables['islandora_dublin_core'] = isset($dc_object) ? $dc_object : NULL;
  $variables['dc_array'] = isset($dc_object) ? $dc_object->asArray() : array();
  $variables['islandora_object_label'] = $object->label;
  $variables['theme_hook_suggestions'][] = 'islandora_remote_media__' . str_replace(':', '_', $object->id);
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($object);
  $variables['metadata'] = islandora_retrieve_metadata_markup($object);
  $variables['description'] = islandora_retrieve_description_markup($object);

  $viewer_dsid = 'OBJ';

  $media_params = array(
    'pid' => $object->id,
  );
  // Media player.
  if (isset($object[$viewer_dsid]) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $object[$viewer_dsid])) {
    $embedded_media = $object[$viewer_dsid]->content;
  } 

  // Thumbnail.
  if (isset($object['TN']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $object['TN'])) {
    $media_params += array(
      'tn' => url("islandora/object/{$object->id}/datastream/TN/view", array('absolute' => TRUE)),
    );
  }

  $variables['islandora_content'] = '';
  if ($embedded_media) {
    $variables['islandora_content'] = $embedded_media;
  }
  else {
    $variables['islandora_content'] = NULL;
  } 
  return array('' => $embedded_media);
}
