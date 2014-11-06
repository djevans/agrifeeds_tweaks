<?php
/**
 * Created by PhpStorm.
 * User: david
 * Date: 05/11/14
 * Time: 13:10
 */

class sparqly_tweaks_handler_filter_field_value extends sparql_views_handler_filter_field_value {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function operators() {
    return array(
      '!=' => array(
        'title' => t('Is not bound'),
        'short' => t('!BOUND()'),
        'method' => 'op_not_bound',
        'values' => 1,
      ),
    );
  }

  /**
   * Operator; Uses SPARQL's FILTER with !BOUND().
   */
  function op_not_bound() {
    $value = ''; //@TODO changeme
    $this->query->add_filter('!BOUND', $value);
  }
}