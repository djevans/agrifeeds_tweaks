<?php
/**
 * Created by PhpStorm.
 * User: david
 * Date: 05/11/14
 * Time: 13:10
 */
class agrifeeds_tweaks_handler_filter_field_value extends sparql_views_handler_filter_field_value {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function operators() {
    $operators = parent::operators();
    $operators['!='] = array(
      'title' => t('Is not equal to'),
      'short' => t('!='),
      'method' => 'op_not_equal',
      'values' => 1,
    );
    return $operators;
  }

  function op_not_equal($field_name) {

    $value_type = $this->options['sparql_options']['value_type'];
    $language = $this->options['sparql_options']['language'];

    $object = '?var' . rand();
    $values = preg_split('/,\s/', $this->value);
    foreach ($values as $value) {
      $val = $this->query->format_replacement($value, $value_type, $language);
      $this->query->filters[] = '(STR(' . $object . ') != "' . $val . '")';
    }

    $relationship = $this->options['relationship'];

    if ($relationship == 'none') {
      $subject = $this->definition['subject'];
    }
    else {
      $subject = $relationship;
    }
    $predicate = $this->definition['rdf_mapping'][0];
    $this->query->add_triple($subject, $predicate, $object);


  }
}
