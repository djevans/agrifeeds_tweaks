<?php

/**
 * @file
 *
 * Feeds Tamper plugin to return the 2-letter ISO code for a language,
 * given its name in English.
 */

$plugin = array(
  'form' => 'agrifeeds_tweaks_language_plugin_form',
  'callback' => 'agrifeeds_tweaks_language_plugin_callback',
  'name' => 'Language Plugin',
  'multi' => 'loop',
  'category' => 'SPARQL Views',
  'default description' => "Get a language's ISO code, given its name",
);

function agrifeeds_tweaks_language_plugin_form($importer, $element_key, $settings) {

  $form = array();
  $form['help'] = array(
    '#markup' => t("Matches on the language's name"),
  );

  return $form;

}

function agrifeeds_tweaks_language_plugin_callback($source, $item_key, $element_key, &$field, $settings) {

  include_once DRUPAL_ROOT . '/includes/iso.inc';

  $iso_codes = _locale_get_predefined_list();

  // Values are arrays of variable length.
  foreach ($iso_codes as $iso_code => $language_names) {
    if (in_array($field, $language_names)) {
      // Certain ISO codes have more than 2 characters,
      // such as 'en-gb' (British English) and 'pt-br' (Brazilian Portuguese).
      // In these cases, we only need the first 2 characters.
      $field = substr($iso_code, 0, 2);
      break;
    }
  }

}

