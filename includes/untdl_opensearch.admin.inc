<?php

/**
 * @file
 * Admin menu configurations and submit callback function
 */

use UntLibraries\OpensearchClient\Client;

/**
 * Implements hook_search_admin().
 */
function untdl_opensearch_search_admin() {
  $form['untdl_opensearch'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNT Libraries Digital Collections Opensearch'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['untdl_opensearch']['untdl_opensearch_document_url'] = array(
    '#title' => t('Opensearch Document URL'),
    '#type' => 'textfield',
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => variable_get('untdl_opensearch_document_url', ''),
    '#description' => t('The URL to the Opensearch description document'),
  );

  $form['untdl_opensearch']['untdl_opensearch_search_path'] = array(
    '#title' => t('Search Path'),
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('untdl_opensearch_search_path', ''),
    '#required' => FALSE,
  );

  $form['untdl_opensearch']['untdl_opensearch_block_title'] = array(
    '#title' => t('Search Block Title'),
    '#type' => 'textfield',
    '#size' => 20,
    '#required' => FALSE,
    '#default_value' => variable_get('untdl_opensearch_block_title', ''),
    '#description' => t('Title given to the included Opensearch block. This can also be configured through the block configuration menu. If a title is configured in this menu, it will override any settings within the block configuration menu.'),
  );

  $form['untdl_opensearch']['untdl_opensearch_search_button'] = array(
    '#title' => t('Submit Button Text'),
    '#type' => 'textfield',
    '#size' => 20,
    '#required' => FALSE,
    '#default_value' => variable_get('untdl_opensearch_search_button'),
    '#description' => t('Text displayed in the submit button for the Opensearch block. Defaults to "Submit"'),
  );

  $form['untdl_opensearch']['untdl_opensearch_date_format'] = array(
    '#title' => t('Date & Time Setting'),
    '#type' => 'select',
    '#options' => array(
      'short' => t('Short'),
      'medium' => t('Medium'),
      'long' => t('Long'),
    ),
    '#default_value' => variable_get('untdl_opensearch_date_format', 'short'),
    '#description' => t('Formatting for the Updated and Published elements'),
  );

  $form['untdl_opensearch']['untdl_opensearch_show_entry_info'] = array(
    '#title' => t('Show entry information'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('untdl_opensearch_show_entry_info', 0),
    '#description' => t('Displays Updated date and Published date if available'),
  );

  $form['untdl_opensearch']['untdl_opensearch_show_thumbnail'] = array(
    '#title' => t('Attempt to show thumbnails'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('untdl_opensearch_show_thumbnail', 0),
    '#description' => t('When enabled, this option will attempt to display thumbnails that may be in the indivdual search results'),
  );

  $form['untdl_opensearch']['untdl_opensearch_target_blank'] = array(
    '#title' => t('Follow search results in a new tab/window'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('untdl_opensearch_target_blank', 0),
    '#description' => t('When enabled, this option adds "target=_blank" to each result link. Most browsers interpret this as "Open link in a new tab"'),
  );

  $form['#submit'][] = 'untdl_opensearch_admin_settings_submit';

  return $form;
}


/**
 * Supplemental callback.
 *
 * Fired upon saving search configuration settings.
 *
 * Parses the Opensearch Description Document at the provided link, and
 * saves the parsed url template into the variable 'untdl_opensearch_search_url'
 */
function untdl_opensearch_admin_settings_submit($form, &$form_state) {
  // Set the Document URL; Required field.
  variable_set('untdl_opensearch_document_url', $form_state['values']['untdl_opensearch_document_url']);

  // Set the search path if given.
  // Delete the variable if it was blank and existed previously.
  if (!empty($form_state['values']['untdl_opensearch_search_path'])) {
    variable_set('untdl_opensearch_search_path', $form_state['values']['untdl_opensearch_search_path']);
  }
  else {
    variable_del('untdl_opensearch_search_path');
    unset($form_state['values']['untdl_opensearch_search_path']);
  }

  // Set the block title if given.
  // Delete the variable if it was blank and existed previously.
  if (!empty($form_state['values']['untdl_opensearch_block_title'])) {
    variable_set('untdl_opensearch_block_title', $form_state['values']['untdl_opensearch_block_title']);
  }
  else {
    variable_del('untdl_opensearch_block_title');
    unset($form_state['values']['untdl_opensearch_block_title']);
  }

  // Set the search button text if given.
  // Delete the variable if it was blank and existed previously.
  if (!empty($form_state['values']['untdl_opensearch_search_button'])) {
    variable_set('untdl_opensearch_search_button', $form_state['values']['untdl_opensearch_block_title']);
  }
  else {
    variable_del('untdl_opensearch_search_button');
    unset($form_state['values']['untdl_opensearch_search_button']);
  }

  variable_set('untdl_opensearch_date_format', $form_state['values']['untdl_opensearch_date_format']);

  variable_set('untdl_opensearch_show_entry_info', $form_state['values']['untdl_opensearch_show_entry_info']);

  // Set value for showing thumbnails.
  variable_set('untdl_opensearch_show_thumbnail', $form_state['values']['untdl_opensearch_show_thumbnail']);

  // Set value for opening search links in a new tab.
  variable_set('untdl_opensearch_target_blank', $form_state['values']['untdl_opensearch_target_blank']);

  $document_url = $form_state['values']['untdl_opensearch_document_url'];

  // Find the Opensearch Description Document and get Url template.
  $search_client = new Client();
  try {
    $search_client->configure($document_url);
  }
  catch (Exception $e) {
    watchdog('untdl_opensearch', $e->getMessage());
  }

  $document = $search_client->document;

  // Set the template to a variable or notify the document was not found.
  if ($document->getTemplate()) {
    $template = $document->getTemplate();
    variable_set('untdl_opensearch_search_template', $template);

    drupal_set_message("The Opensearch Document was retrieved.");
  }
  else {
    drupal_set_message("Unable to locate the Opensearch Document at the specified URL. This module only supports Description Documents that contain URL types of application/atom+xml", 'error');
  }
}
