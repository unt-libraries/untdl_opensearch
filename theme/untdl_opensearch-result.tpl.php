<?php

/**
 * @file
 * Default theme implementation for displaying a single search result from the
 * untdl_opensearch module.
 *
 * This template renders a single search result and is collected into
 * search-results.tpl.php. This and the parent template are
 * dependent to one another sharing the markup for definition lists.
 *
 * Modelled after search-result.tpl.php from the search module
 */
?>
<li class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <div>
    <?php if ($thumbnail): ?>
      <div class="thumbnail">
        <img src=<?php print $thumbnail; ?>>
      </div>
    <?php endif; ?>
    <h3 class="title"<?php print $title_attributes; ?>>
      <a href="<?php print $url; ?>" target="<?php print $target; ?>"><?php print $title; ?></a>
    </h3>
    <?php print render($title_suffix); ?>
    <div class="search-snippet-info">
      <?php if ($content): ?>
        <p class="search-snippet"<?php print $content_attributes; ?>>
          <?php print $content; ?>
        </p>
      <?php endif; ?>
    </div>
    <?php if ($info): ?>
      <p class="search-info">
        <?php if (isset($info_split['updated'])): ?>
          <span class="untdl-opensearch-info-label">Updated: </span>
          <span><?php print $info_split['updated']; ?></span>
          <br />
        <?php endif; ?>
        <?php if (isset($info_split['published'])): ?>
          <span class="untdl-opensearch-info-label">Published: </span>
          <span><?php print $info_split['published']; ?></span>
        <?php endif; ?>
      </p>
    <?php endif; ?>
  </div>
</li>
