<?php

/**
 * Implements hook_drush_command().
 */
function US22117_drush_command() {
  $items['US22117_communities'] = array(
    'description' => 'Module to migrate Forum taxonomy into organic groups. Assign community topics and members to respective newly created groups. ',
    'access arguments' => array('access content'),
    'aliases' => array('mfc')
  );
  return $items;
}

/**
 * Function that creates organic groups, Assign community topics and members to respective groups .
 */
function drush_US22117_communities(){
  $transaction = db_transaction();
  $vocab = 'forums';
  try{
    drush_print(dt('Creating Groups based on taxonomy '));
    $term_node_map =  US22117_create_groups($vocab,'community');
    drush_print(dt('Assigning community topics to their respected groups'));
    US22117_update_communitytopics($term_node_map);
    drush_print(dt('Community topics updated successfully '));
    US22117_add_users_to_group($term_node_map);
    drush_print(dt('People added to groups successfully '));
    drush_print(dt('Migration successfully completed '));
    return;
  }
  catch (Exception $e) {
    $transaction->rollback();
    echo "Rolling back Transactions.";
    watchdog_exception('my_type', $e);
    exit();
  }
}
