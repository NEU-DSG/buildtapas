<?php

define (
	'ANONYMOUS_BASE_PERMISSIONS',
	array(
		'access content',
		'access comments',
	)
);

define (
	'REGISTERED_BASE_PERMISSIONS',
	array_merge(
		ANONYMOUS_BASE_PERMISSIONS,
		array(
			'post comments',
			'skip comment approval',
			'access user contact forms',
			'use text format filtered_html',
			'edit own follow links', #follow module
			'view own unpublished content',
			'edit own main profile', #profile2 module
			'view own main profile', #profile2 module
			'view any main profile', #profile2 module
			'search content',
			'use advanced search',
			'view user profiles',
			'cancel account',
		)
	)
);

define (
	'PAIDMEMBER_BASE_PERMISSIONS',
	array_merge(
		REGISTERED_BASE_PERMISSIONS,
		array(
			'edit own comments',
			'use text format full_html',
			'change own username',
		)
	)
);


define (
	'SITEEDITOR_BASE_PERMISSIONS',
	array_merge(
		PAIDMEMBER_BASE_PERMISSIONS,
		array(
			'edit site follow links', #follow module
			'change link titles', #follow module
			'administer forums',
			'bypass node access',
			'access content overview',
			'view revisions',
			'revert revisions',
			'delete revisions',
			'administer url aliases',
			'create url aliases',
			'administer profile types', #profile2 module
			'administer profiles', #profile2 module
			'edit any main profile', #profile2 module
			'administer sharethis', #sharethis module
			'access site in maintenance mode',
			'block ip addresses',
			'access all views'
		)
	)
);

/**
 * Set up permissions used by all registered users
 */
function tapas_registered_user_setup() {

  variable_set('user_pictures', '1');
  variable_set('user_picture_dimensions', '1024x1024');
  variable_set('user_picture_file_size', '800');
  variable_set('user_picture_style', 'thumbnail');

  variable_set('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);

	$content_perms = _tapas_content_permissions_loop(
		array(
			'tapasrecordnode',
			'forum'
		),
		array(
			'create',
			'edit own',
			'delete own'
		)
	);
	user_role_grant_permissions(
		DRUPAL_AUTHENTICATED_RID, 
		array_merge(
			REGISTERED_BASE_PERMISSIONS, 
			$content_perms)
	);
}

/**
 * Set up permissions for paid TEI members
 */

function tapas_paidmember_user_setup() {

	$tapas_content_perms = _tapas_content_permissions_loop(
		array(
			'tapascollection_project',
			'tapascollection_collection',
			'tapasrecordnode',
			'forum'),
		array(
			'create',
			'edit own',
			'delete own'
		)
	);

	$general_content_perms = _tapas_content_permissions_loop(
		array(
			'tapasrecordnode'
		),
		array(
			'edit any',
			'delete any'
		)
	);

	_tapas_create_role(
		'paidmember',
		array_merge(
			PAIDMEMBER_BASE_PERMISSIONS,
			$tapas_content_perms,
			$general_content_perms
		),
		3
	);
}


/**
 * Set up permissions for site editor (admin lite)
 */
function tapas_siteeditor_user_setup() {


	$content_perms = _tapas_content_permissions_loop(
		array(
			'tapascollection_project',
			'tapascollection_collection',
			'tapasrecordnode',
			'forum',
			'tapas_newsitem',
			'tapas_staticpage',
		),
		array(
			'create',
			'edit own',
			'edit any',
			'delete own',
			'delete any')
	);

	_tapas_create_role(
		'siteeditor',
		array_merge(
			SITEEDITOR_BASE_PERMISSIONS,
			_tapas_siteeditor_base_permissions()
		),
		4
	);

}

/**
 * Set up permissions for site administrator
 */
function tapas_administrator_user_setup() {

	$admin_permissions = array_keys(module_invoke_all('permission'));

	$admin_role = _tapas_create_role('administrator', $admin_permissions,	 5);


  // Set this as the administrator role.
  variable_set('user_admin_role', $admin_role->rid);

  // Assign user 1 the "administrator" role.
  db_insert('users_roles')
		->fields(array('uid' => 1, 'rid' => $admin_role->rid))
    ->execute();
	
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

/**
 * Shorthand for building permissions arrays
 */

function _tapas_content_permissions_loop($types, $perms) {

	
	$result = array();

	foreach ($types as $type) {
		foreach ($perms as $perm) {
			$result[] = "$perm $type content";
		}
	}

	return $result;

}
