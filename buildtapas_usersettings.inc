<?php

function tapas_user_setup() {

	echo "DEBUGGING: tapas_user_setup() called
	";

  // Enable user picture support and set the default to a square thumbnail option.
  variable_set('user_pictures', '1');
  variable_set('user_picture_dimensions', '1024x1024');
  variable_set('user_picture_file_size', '800');
  variable_set('user_picture_style', 'thumbnail');

  // Allow visitor account creation with administrative approval.
  variable_set('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);

  // Enable default permissions for system roles.
	
	$anonymous_permissions = array(
		'filtered_html_format',
		'access content',
		'access comments',
	);
	echo "DEBUGGING: var_dump(anonymous_permissions) is: " . var_dump($anonymous_permissions) . "
	";

	$registered_permissions = array_merge(
		$anonymous_permissions,
		array(
			'post_comments',
			'skip_comment_approval'));

	echo "DEBUGGING: var_dump(registered_permissions) is: " . var_dump($registered_permissions) . "
	";

	$paidmember_permissions = array_merge(
		$registered_permissions,
		array());

	echo "DEBUGGING: var_dump(paidmember_permissions) is: " . var_dump($paidmember_permissions) . "
	";


	echo "DEBUGGING: About to call user_role_grant_permissions
	";

	user_role_grant_permissions(DRUPAL_ANONYMOUS_RID, $anonymous_permissions);
	user_role_grant_permissions(DRUPAL_AUTHENTICATED_RID, $registered_permissions);

	echo "DEBUGGING: Create roles
	";
	// Create Roles
	$admin_permissions = array_keys(module_invoke_all('permission'));

	_tapas_create_role('paidmember', $paidmember_permissions, 3);
	$admin_role = _tapas_create_role('administrator', $admin_permissions,	 4);

	echo "DEBUGGING: Set administrator role
	";

  // Set this as the administrator role.
  variable_set('user_admin_role', $admin_role->rid);

  // Assign user 1 the "administrator" role.
  db_insert('users_roles')
		->fields(array('uid' => 1, 'rid' => $admin_role->rid))
    ->execute();
	
	echo "DEBUGGING: tapas_user_setup() completed.
	";
}

/**
 * Creates a role with the given name and permissions.
 */
function _tapas_create_role($rolename, $permissions, $weight) {

	$new_role = new stdClass();
	$new_role->name = $rolename;
	$new_role->weight = $weight;

	user_role_save($new_role);
	user_role_grant_permissions($new_role->rid, $permissions);

	return $new_role;

}
