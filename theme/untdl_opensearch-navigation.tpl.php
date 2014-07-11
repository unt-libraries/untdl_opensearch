<?php
/**
 * @file
 * Custom pager for untdl_opensearch
 *
 * Rendered by @see template_preprocess_untdl_opensearch_search_results()
 * 
 * @see template_preprocess_untdl_opensearch_navigation()
 */
?>
<?php if ($has_links): ?>
  <div id="untdl-navigation" class="untdl-navigation">
    <?php if ($has_links): ?>
      <div class="page-links clearfix">
      <?php if ($first_url): ?>
        <a href="<?php print $first_url; ?>" class="page-previous" title="<?php print t('Go to first page'); ?>"><?php print t('‹‹First');  ?></a>
      <?php endif; ?>
      <?php if ($prev_url): ?>
        <a href="<?php print $prev_url; ?>" class="page-previous" title="<?php print t('Go to previous page'); ?>"><?php print t('‹Prev'); ?></a>
      <?php endif; ?>
      <?php if($range): ?>
        <?php foreach($range as $key => $value): ?>
          <?php if ($key == $current_page): ?>
            <span class="page-numbered"><?php print t('@current_page', array('@current_page' => $current_page));?></span>
          <?php else: ?>
            <a href="<?php print $value; ?>" class="page-numbered"><?php print $key; ?></a>
          <?php endif; ?>
        <?php endforeach; ?>
      <?php endif; ?>
      <?php if ($next_url): ?>
        <a href="<?php print $next_url; ?>" class="page-next" title="<?php print t('Go to next page'); ?>"><?php print t('Next›'); ?></a>
      <?php endif; ?>
      <?php if ($last_url): ?>
        <a href="<?php print $last_url; ?>" class="page-next" title="<?php print t('Go to last page'); ?>"><?php print t('Last››');  ?></a>
      <?php endif; ?>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
