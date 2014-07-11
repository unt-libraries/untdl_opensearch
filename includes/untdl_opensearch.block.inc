<?php

/**
 * @file
 * Block configuration
 */

/**
 * Implements hook_block_info().
 */
function untdl_opensearch_block_info() {
  $blocks['untdl_opensearch'] = array(
    'info' => t('UNT Libraries Digital Collections Opensearch'),
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function untdl_opensearch_block_view($delta = '') {
  $block = array();
  switch ($delta) {
    case 'untdl_opensearch':
      $title = variable_get('untdl_opensearch_block_title', FALSE);

      if ($title) {
        $block['title'] = t('@title', array('@title' => $title));
      }

      $block['content'] = drupal_get_form('untdl_opensearch_search_block_form');
      break;
  }

  return $block;
}

/**
 * Block form.
 */
function untdl_opensearch_search_block_form($form, &$form_state) {
  $form['keys'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#required' => TRUE,
  );

  $submit = variable_get('untdl_opensearch_search_button', 'Submit');

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('@submit', array('@submit' => $submit)),
  );

  return $form;
}

/**
 * Submit callback for Block Form.
 */
function untdl_opensearch_search_block_form_submit($form, &$form_state) {
  $path = variable_get('untdl_opensearch_search_path', 'untdl_opensearch');
  drupal_goto("search/$path/" . $form_state['values']['keys']);
}
