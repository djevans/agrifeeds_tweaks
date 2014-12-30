<?php
/**
 * Created by PhpStorm.
 * User: david
 * Date: 27/11/14
 * Time: 22:49
 */

class agrifeeds_tweaks_handler_filter_is_of_datatype extends sparql_views_handler_filter {

  function operators() {
    $operators['datatype'] = array(
      'title' => 'Is of data type',
      'short' => 'DATATYPE()',
      'method' => 'op_is_of_datatype',
      'values' => 1,
    );
    return $operators;
  }

  function admin_summary() {
    $output = $this->operator . ' ';
    $output .= check_plain($this->options['value']);
    return $output;
  }

  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
  }

  function op_is_of_datatype($field_name) {
    $value = $this->query->format_replacement($this->options['value'], 'uri');

    $relationship = $this->options['relationship'];

    if ($relationship == 'none') {
      $subject = $this->definition['base field'];
    }
    else {
      $subject = $relationship;
    }

    $this->query->add_filter('=', array('DATATYPE(?' . $subject .')', '"' . $value . '"'));
  }

}
