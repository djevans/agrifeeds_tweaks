<?php

/**
 *  Implements hook_views_data_alter().
 */
function agrifeeds_tweaks_views_data_alter(&$data) {

  $entity_info = entity_get_info(SPARQL_VIEWS_ENTITY);

  foreach (sparql_views_get_endpoints() as $endpoint) {

    $table_id = $endpoint->table_id;
    if (isset($data[$table_id]) && isset($data[$table_id]['table'])) {

      // Get the resource types that pertain to this endpoint.
      $select = db_select('sparql_views_resource_type', 'svrt')
        ->fields('svrt', array('name'));
      $select->join(
        'sparql_views_resource_type_endpoint',
        'e',
        'svrt.id = e.svid AND e.endpoint_uri = :endpoint',
        array(':endpoint' => $endpoint->uri)
      );
      $resource_types = $select->execute()->fetchCol();

      foreach ($resource_types as $resource_type) {
        $group = $entity_info['bundles'][$resource_type]['label'];
        // Alter the filter handler for mapped fields.
        $rdf_mapping = $entity_info['bundles'][$resource_type]['rdf_mapping'];
        $extra_filters = array();
        foreach ($rdf_mapping as $field_name => $field) {
          if ('rdftype' == $field_name) {
            continue;
          }
          $field_index = $resource_type . '_' . $field_name;

          $data[$table_id][$field_index]['filter']['handler'] = 'agrifeeds_tweaks_handler_filter_field_value';

          $extra_filters[$field_index . '_is_uri']['filter'] = array(
            'title' => t($field_name . ' is URI'),
            'help' => t('Require the subject to be a URI.'),
            'group' => t($group),
            'base' => $endpoint->table_id,
            'base field' => $field_index,
            'handler' => 'agrifeeds_tweaks_handler_filter_is_uri',
            'label' => t('isURI()'),
            'rdf_mapping' => $field['predicates'],
            'subject' => $resource_type,
          );
          $extra_filters[$field_index . '_is_of_datatype']['filter'] = array(
            'title' => t($field_name . ' datatype'),
            'help' => t('Constrain the datatype of the subject.'),
            'group' => t($group),
            'base' => $endpoint->table_id,
            'base field' => $field_index,
            'handler' => 'agrifeeds_tweaks_handler_filter_is_of_datatype',
            'label' => t('DATATYPE()'),
            'rdf_mapping' => $field['predicates'],
            'subject' => $resource_type,
          );
          $extra_filters[$field_index . '_not_bound']['filter'] = array(
            'title' => t($field_name . ' not bound'),
            'help' => t('Require that the subject is not bound.'),
            'group' => t($group),
            'base' => $endpoint->table_id,
            'base field' => $field_index,
            'handler' => 'agrifeeds_tweaks_handler_filter_not_bound',
            'label' => t('!BOUND()'),
            'rdf_mapping' => $field['predicates'],
            'subject' => $resource_type,
          );
        }
        $data[$table_id] = array_merge($data[$table_id], $extra_filters);
      }
    }
  }

}
