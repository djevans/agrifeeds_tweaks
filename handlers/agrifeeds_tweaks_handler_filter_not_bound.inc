<?php
/**
 * Created by PhpStorm.
 * User: david
 * Date: 02/12/14
 * Time: 10:47
 */

class agrifeeds_tweaks_handler_filter_not_bound extends sparql_views_handler_filter {

  function operators() {
    $operators['not_bound'] = array(
      'title' => 'Not Equal To',
      'short' => '!BOUND',
      'method' => 'op_not_bound',
      'values' => 1,
    );
    return $operators;
  }

  function op_not_bound($field_name) {

    $relationship = $this->options['relationship'];

    if ($relationship == 'none') {
      $subject = $this->definition['subject'];
    }
    else {
      $subject = $relationship;
    }

    $this->query->add_filter('!BOUND', array($subject));

  }

} 