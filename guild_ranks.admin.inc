<?php
/**
 * @file
 * Administrative page callbacks for the guild_ranks module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function guild_ranks_admin_settings_form($form_state) {
	//Debug
	//echo '<p>Field Name: '.variable_get('guild_ranks_field', '').'</p>';
	//echo '<p>Admin ID: '.variable_get('guild_superadmin_role', '').'</p>';
	
	//echo'<pre>';print_r(field_info_fields());echo'</pre>';
	$field_info = field_info_fields();
	$drupal_roles = user_roles();
	
	//For security we do not want to accidently set anonymous role 
	//Provide ksort() assuming original administrator role still active
	unset($drupal_roles[DRUPAL_ANONYMOUS_RID]);
	ksort($drupal_roles);
	
	$array_fields = array();
	$guild_taxonomy = array();
	
	$array_fields['0'] = 'Empty';
	foreach($field_info as $field_item) {
		if(!empty($field_item['bundles']['user']) && !empty($field_item['settings']['allowed_values'][0]['vocabulary'])) {
			//$guild_taxonomy[] = $field_item['settings']['allowed_values'][0]['vocabulary'];
			$array_fields[$field_item['field_name']] = $field_item['field_name'];
		}
	}
	
	if($user_field = variable_get('guild_ranks_field', '')) {
		//echo'<pre>';print_r($field_info[$user_field]);echo'</pre>';
		$vocabularies = taxonomy_vocabulary_get_names();
		$tax_machine_name = $field_info[$user_field]['settings']['allowed_values'][0]['vocabulary'];
		$guild_tax_vid = $vocabularies[$tax_machine_name]->vid;
		//echo'<pre>';print_r($vocabularies[$tax_machine_name]);echo'</pre>';
		
		//echo'<pre>';print_r(taxonomy_get_tree($guild_tax_vid));echo'</pre>';
		$guild_tax_tree = taxonomy_get_tree($guild_tax_vid);
		
		foreach($guild_tax_tree as $term) {
			$guild_taxonomy[$term->tid] = $term->name;
		}
	}
	//echo'<pre>';print_r($drupal_roles);echo'</pre>';
	//echo'<pre>';print_r($array_fields);echo'</pre>';
	//echo'<pre>';print_r($guild_taxonomy);echo'</pre>';
	
  $form['ranks'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['ranks']['guild_ranks_field'] = array(
    '#title' => t('User Field'),
    '#type' => 'select',
    '#options' => $array_fields,
    '#default_value' => variable_get('guild_ranks_field', ''),
    '#size' => 1,
    '#required' => TRUE,
    '#description' => t('This field will be monitored on user account updates to adjust changes in role permissions.'),
  );
  $form['ranks']['guild_superadmin_role'] = array(
    '#title' => t('Super Admin Role'),
    '#type' => 'select',
    '#options' => $drupal_roles,
    '#default_value' => variable_get('guild_superadmin_role', ''),
    '#size' => 1,
    '#required' => TRUE,
    '#description' => t('If a user is given this role, it will be kept on saves. Allows individual users to have admin access without changing guild rank.'),
  );
  $form['relationships'] = array(
  	'#type' => 'fieldset',
  	'#title' => 'Taxonomy to Roles relationship'
  );
  foreach($guild_taxonomy as $rank => $name) {
  	$form['relationships']['guild_rank_'.$rank] = array(
  	  '#title' => t($name),
	  '#type' => 'select',
	  '#options' => $drupal_roles,
	  '#default_value' => variable_get('guild_rank_'.$rank),
	  '#size' => 1,
	  '#description' => 'The role that '.$name.' should be assigned to'
	);
  }
  return system_settings_form($form);
}
?>