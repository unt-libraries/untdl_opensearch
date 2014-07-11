<?php
/**
 * @file
 * Preprocessing functions for module template files
 */

/**
 * Process variables for untdl_opensearch-results.tpl.php.
 *  
 *  - $results: Instance of \UntLibraries\Opensearch\Response\Client
 *  - $module: Module that the results came from.
 *
 * @see untdl_opensearch-results.tpl.php
 */
function template_preprocess_untdl_opensearch_results(&$variables) {
  $variables['search_results'] = '';

  if (!empty($variables['module'])) {
    $variables['module'] = check_plain($variables['module']);
  }

  $search_client = $variables['results'];
  $results = $search_client->response;
  if (!is_null($results)) {

    $variables['executed'] = TRUE;

    foreach ($results->getResults() as $result) {
      $variables['search_results'] .= theme(
        'untdl_opensearch_result',
        array(
          'result' => $result,
          'module' => $variables['module'],
        )
      );
    }

    $variables['start_index'] = $results->getStartIndex();
    $variables['end_index'] = $results->calculateEndIndex();
    $variables['total_results'] = $results->getTotalResults();
    $variables['current_page'] = $results->searchQuery->getStartPage();
    $variables['num_pages'] = $results->getNumPages();

    $navigation = $search_client->navigation;
    $variables['pager'] = theme(
      'untdl_opensearch_navigation',
      array(
        'page_info' => $navigation,
        'module' => $variables['module'],
      )
    );

    $variables['theme_hook_suggestions'][] = 'search_results__' . $variables['module'];
  }
  else {
    $variables['executed'] = FALSE;
  }

}

/**
 * Process variables for untdl_opensearch-result.tpl.php.
 *
 *  - $result: Instance of \UntLibraries\OpensearchClient\Response\Entry
 *  - $module: The module the results came from
 *
 * @see untdl_opensearch-result.tpl.php
 */
function template_preprocess_untdl_opensearch_result(&$variables) {
  $result = $variables['result'];
  $variables['url'] = check_url($result->link);
  $variables['title'] = check_plain($result->title);

  $thumbnail = variable_get('untdl_opensearch_show_thumbnail', FALSE);
  if ($thumbnail) {
    $thumbnail = $result->thumbnail;
  }
  $variables['thumbnail'] = $thumbnail;

  // Check for existence. User search does not include snippets.
  $variables['content'] = isset($result->content) ? $result->content : '';

  // Provide separated and grouped meta information.
  $date_format = variable_get('untdl_opensearch_date_format', 'short');

  // Set updated field using defined date format.
  $info = variable_get('untdl_opensearch_show_entry_info', FALSE);
  if ($info) {
    $info = array();

    if ($result->updated) {
      $updated = format_date($result->updated->format('U'), $date_format);
      $info['updated'] = $updated;
    }

    // Set published field using defined date format.
    if ($result->published) {
      $published = format_date($result->published->format('U'), $date_format);
      $info['published'] = $published;
    }

    if ($result->id) {
      $info['id'] = sprintf('ID: %s', $result->id);
    }

    $variables['info_split'] = $info;
    $variables['info'] = implode(' - ', $info);
  }
  else {
    $variables['info'] = FALSE;
  }
  $variables['theme_hook_suggestions'][] = 'search_result__' . $variables['module'];

  if (variable_get('untdl_opensearch_target_blank', 0)) {
    $variables['target'] = '_blank';
  }
  else {
    $variables['target'] = '_self';
  }
}

/**
 * Process variables for untdl_opensearch-navigation.tpl.php.
 *
 *  - $page_info: Instance of UntdlNavigation 
 *  - $module: The module that executed the search
 *
 * @see untdl_opensearch-navigation.tpl.php
 * @see untdl_opensearch.navigation.inc
 */
function template_preprocess_untdl_opensearch_navigation(&$variables) {
  $navigation = $variables['page_info'];

  $variables['has_links'] = $navigation->getTotalResults() > $navigation->getItemsPerPage();
  $variables['prev_url'] = $navigation->getPrevUrl();
  $variables['prev_page'] = $navigation->getStartPage() - 1;
  $variables['next_url'] = $navigation->getNextUrl();
  $variables['next_page'] = $navigation->getStartPage() + 1;;
  $variables['first_url'] = $navigation->getFirstUrl();
  $variables['last_url'] = $navigation->getLastUrl();
  $variables['current_page'] = $navigation->getStartPage();
  $variables['num_pages'] = $navigation->getNumPages();
  $variables['range'] = $navigation->makePagerRange();
}
