# UNT Digital Collections Opensearch

A Drupal 7 search module for Opensearch compatible resources.

## Overview


Module machine name: __untdl_opensearch__

Dependencies: 

 * Drupal 7.x
 * PHP >= 5.3.3 
 * [unt-libraries/opensearch-client](https://github.com/unt-libraries/opensearch-client)
 * Drupal Search Module
 * Drupal Libraries API (https://drupal.org/project/libraries)
 * X Autoload (https://drupal.org/project/xautoload)

Optional:
 - Drupal Custom Search Module


## Installation
1. Install and enable Drupal Libraries API and X Autoload. 

2. Clone the unt-libraries/opensearch-client repository into your libraries directory
    - Refrain from renaming the cloned repository directory. X Autoload looks for the library by directory name for autoloading

3. Clone the module into your installed modules location (i.e. sites/all/modules)

4. Enable the module in  *Administration* > *Modules*


## Configuration

Despite enabling the module, the untdl_opensearch search option will be marked as inactive by default in *Administration* > *Configuration* > *Search settings*

1. In *Administration* > *Configuration* > *Search settings*, enable the option "UNT Libraries Digital Collections Opensearch", and save the configuration

     If you did not have the Drupal Search module enabled previous to installing **untdl_opensearch**, then there may be other searches active (Node and User). Those can be disabled if desired. 

2. After saving, the UNT Libraries Digital Collections Opensearch configuration menu will be available on the *Search settings* page. Put in the URL to the Opensearch description document and save the configuration. 

*There are a number of aesthetic options available for configuration as well. If you set a custom search path, be sure to clear the cache after.*

## Additional Options

- Custom search path
- Search Block
    - Custom Block Title and Submit button text
- Various search result display options

## Permissions

This module borrows the Drupal Search module permissions

- administer search
- search content
- use advanced search 
    
__Note:__ There are currently no advanced search options associated with this module.
    

## Extending

Each entry of the atom feed is expected to look something like this in order to work with the templates included in the module.

``` xml
<entry>
    <title>Example Entry</title>
    <link href="http://texashistory.unt.edu/ark:/67531/metapth60888/"/>
    <id>ark:/67531/metapth60888</id>
    <updated>2012-07-09T10:22:25Z</updated>
    <published>2009-11-12T15:16:28Z</published>
    <content type="text">Lorem ipsum Dolore culpa ex dolore in ex nisi aliquip eiusmod ad ut eu mollit aliquip in.</content>
    <media:thumbnail url="http://texashistory.unt.edu/ark:/67531/metapth60888/thumbnail/"/>
</entry>
```


However, if the feed you desire does not match the structure above, The SimpleXMLElement object of the individual entry is available to you in HOOK_preprocess_untdl_opensearch_result().

```php
function HOOK_preprocess_untdl_opensearch_result(&$variables) {
  // Get the object out of variables array
  $result = $variables['result'];  

  //Get the SimpleXMLElement instance
  $entry = $result->getEntry();
  
  // more code here...
}
    
```



## Theming


All the template files are preprocessed using template_preprocess_THEME()

You may influence the variables by implementing your own preprocess function. See https://drupal.org/node/223430 for information on the order in which preprocess functions are executed. 

It is worth noting that untdl_opensearch-results.tpl.php and untdl_opensearch-result.tpl.php work together to create the search results page.

### Hooks

```php
HOOK_preprocess_untdl_opensearch_results()
```
```php
HOOK_preprocess_untdl_opensearch_result()
```
```php
HOOK_preprocess_untdl_opensearch_navigation()
```


### CSS

__Block__
- .block-untdl-opensearch

__Search results__
- .untdl-opensearch-results
 
__Search result__
- .untdl-opensearch-result
	- .thumbnail
	- .title *
	- .search-snippet-info *
	- .search-snippet *
	- .search-info *
	- .untdl-opensearch-info-label

__Navigation__
- .untdl-navigation
	- .page-links
		- .page-previous 
		- .page-numbered
		- .page-next


\* These classes are inherited from the Drupal Search module
