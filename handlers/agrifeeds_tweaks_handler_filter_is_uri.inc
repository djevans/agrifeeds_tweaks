<?php
/**
 * Created by PhpStorm.
 * User: david
 * Date: 25/11/14
 * Time: 10:46
 */

class agrifeeds_tweaks_handler_filter_is_uri extends sparql_views_handler_filter {

  function operators() {
    $operators['is_uri'] = array(
      'title' => 'Is A URI',
      'short' => 'isURI',
      'method' => 'op_is_uri',
      'values' => 0,
    );
    return $operators;
  }

  function query() {
    $field_name = $this->definition['base field'];
    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field_name);
    }
  }

  function op_is_uri($field_name) {
    $this->query->add_filter('isURI', array('?' . $field_name));
  }

}
