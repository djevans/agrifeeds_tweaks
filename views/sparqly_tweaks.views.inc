<?php

/**
 *  Implements hook_views_data_alter().
 */
function sparqly_tweaks_views_data_alter(&$data) {

  foreach (sparql_views_get_endpoints() as $endpoint) {

    // Provide a Views Bulk Operation checkbox.
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
        $title = $data[$table_id][$resource_type]['title'];
        $data[$table_id]['views_bulk_operations_' . $resource_type] = array(
          'title' => 'Content : ' . $title,
          'group' => t('Bulk Operations'),
          'help' => t('Provide a checkbox to select the row for Bulk Operations.'),
          'real field' => $resource_type,
          'field' => array(
            'handler' => 'views_bulk_operations_handler_field_operations',
            'click sortable' => FALSE,
          ),
        );
      }
    }
  }

}
