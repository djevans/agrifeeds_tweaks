<?php
/**
 * @file
 * Feeds Tamper plugin to get a term in the 'Countries' taxonomy by title
 * (3-letter code), given its name (description).
 */

$plugin = array(
  'form' => 'agrifeeds_tweaks_country_plugin_form',
  'callback' => 'agrifeeds_tweaks_country_plugin_callback',
  'name' => 'Country Plugin',
  'multi' => 'loop',
  'category' => 'SPARQL Views',
  'default description' => 'Get a country code, given its name',
);

function agrifeeds_tweaks_country_plugin_form($importer, $element_key, $settings) {
  $form = array();
  $form['help'] = array(
    '#markup' => t("Matches on the taxonomy term's description"),
  );
  return $form;
}

function agrifeeds_tweaks_country_plugin_callback($source, $item_key, $element_key, &$field, $settings) {

  // Given the value of the description, get a term's name.
  $settings['vocabulary'] = 'countries';

  $vocabulary = taxonomy_vocabulary_machine_name_load($settings['vocabulary']);
  if ($vocabulary) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term')
          ->propertyCondition('vid', $vocabulary->vid)
          ->propertyCondition('description', $field);
    $results = $query->execute();
    if (count($results['taxonomy_term']) > 0) {
      $tids = array_keys($results['taxonomy_term']);
      $term = taxonomy_term_load(current($tids));
      $field = $term->name;
    }
  }

}
