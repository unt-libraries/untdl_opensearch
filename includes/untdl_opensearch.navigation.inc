<?php

/**
 * @file
 * Custom Pager.
 *
 * Integrates with UntLibraries\OpensearchClient.
 */


/**
 * Custom Pager/Paginator
 * Built for the untdl_opensearch module
 */
class UntdlNavigation {

  /**
   * Total number of results in the result set
   *
   * @var int
   */
  private $totalResults;

  /**
   * Index for the first result of the current set
   *
   * @var int
   */
  private $startIndex;

  /**
   * Items per page
   *
   * @var int
   */
  private $itemsPerPage;

  /**
   * Start page
   *
   * @var int
   */
  private $startPage;

  /**
   * Number of pages in the result set
   *
   * @var int
   */
  private $numPages;

  /**
   * Constructor.
   *
   * Take the searchQuery object from the search client
   * Pass it back an forth until the searchkeys change.
   *
   * @param \UntLibraries\OpensearchClient\Client $client
   *   Instance of Client after search() has been execute
   */
  public function __construct($client) {
    $this->totalResults = $client->response->getTotalResults();
    $this->startIndex = $client->response->getStartIndex();
    $this->itemsPerPage = $client->response->getItemsPerPage();
    $this->startPage = $client->searchQuery->startPage;
    $this->numPages = $client->response->getNumPages();
  }

  /**
   * Get totalResults.
   *
   * @return int
   *   Total results
   */
  public function getTotalResults() {
    return $this->totalResults;
  }

  /**
   * Get startIndex.
   *
   * @return int
   *   Start index
   */
  public function getStartIndex() {
    return $this->startIndex;
  }

  /**
   * Get itemsPerPage.
   *
   * @return int
   *   Items per page
   */
  public function getItemsPerPage() {
    return $this->itemsPerPage;
  }

  /**
   * Determines the endIndex for each search.
   *
   * @return int
   *   Integer indicated the ending index
   */
  public function calculateEndIndex() {
    $start = $this->getStartIndex();
    $per_page = $this->getItemsPerPage();
    $total = $this->getTotalResults();

    if ($start + $per_page >= $total) {
      $end_index = $total;
    }
    else {
      $end_index = $per_page + $start;
    }

    return $end_index;
  }

  /**
   * Get numPages.
   *
   * @return int
   *   Number of pages
   */
  public function getNumPages() {
    return $this->numPages;
  }

  /**
   * Get startPage.
   *
   * @return int
   *   Start page
   */
  public function getStartPage() {
    return $this->startPage;
  }

  /**
   * Get nextUrl.
   *
   * @return mixed
   *   Next URL or FALSE
   */
  public function getNextUrl() {
    if ($this->getStartPage() < $this->getNumPages()) {
      $next_page = $this->getStartPage() + 1;
      return $this->setupNavigation($next_page);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get prevUrl.
   *
   * @return mixed
   *   Previous URL or FALSE
   */
  public function getPrevUrl() {
    if ($this->getStartPage() > 1) {
      $previous_page = $this->getStartPage() - 1;
      return $this->setupNavigation($previous_page);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get lastUrl.
   *
   * @return mixed
   *   Last URL or FALSE
   */
  public function getLastUrl() {
    if ($this->getStartPage() != $this->getNumPages()) {
      return $this->setupNavigation($this->getNumPages());
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get firstUrl.
   *
   * @return mixed
   *   First URL or FALSE
   */
  public function getFirstUrl() {
    if ($this->getStartPage() != 1) {
      return $this->setupNavigation(1);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Creates a template array for makePagerRange().
   *
   * @return array
   *   Template for makePagerRange() 
   */
  private function calculatePagerRange() {
    $page = $this->getStartPage();
    $end_page = $this->getNumPages();

    switch ($page) {
      case (1 <= $page && 5 >= $end_page):
        $pager = range(1, $end_page);
        break;

      case (1 <= $page && 4 >= $page):
        $pager = range(1, 5);
        break;

      case (5 <= $page && ($end_page - 5) >= $page):
        $pager = range($page - 4, $page + 4);
        break;

      case (($end_page - 4) <= $page && $end_page >= $page):
        $pager = range($end_page - 4, $end_page);
        break;

      default:
        $pager = FALSE;
    }

    return $pager;
  }

  /**
   * Creates and associative array.
   *  
   * @return array
   *   PageNum => URL
   */
  public function makePagerRange() {
    $range = $this->calculatePagerRange();

    if ($range) {
      // All the keys are currently offset by 1 from the page
      // number.
      $range = array_flip($range);

      foreach ($range as $key => $value) {
        $range[$key] = $this->setupNavigation($key);
      }
    }

    return $range;
  }

  /**
   * Processed the URL to get strip out the page number.
   *
   * @return string
   *   URL
   */
  private function setupNavigation($page) {
    $url = preg_split('/[\/]+\d+$/', base_path() . request_path());

    return $url[0] . "/$page";
  }

}
