<?php

function buildtapas_check_permissions_array($perms) {

	$all_perms = array_keys(user_permission_get_modules());
	$err_check = array_diff($perms, $all_perms);

	if ($err_check) {
		echo "
		################################
		found unrecognized permissions:
		";

		foreach ($err_check as $err) {
			echo "$err
			";
		}

		echo "
		################################
		";
		exit(1);
	}

	return $perms;
}



/**
 *	Set up user settings and permissions.
 */
function buildtapas_do_user_settings() {

	echo "DEBUGGING: beginning buildtapas_do_user_settings()
	";

	user_role_grant_permissions(
		DRUPAL_ANONYMOUS_RID,
		_buildtapas_get_anonymous_user_permissions());


	echo "DEBUGGING: finished anonymous grant permissions
	";

  variable_set('user_pictures', '1');
  variable_set('user_picture_dimensions', '1024x1024');
  variable_set('user_picture_file_size', '800');
  variable_set('user_picture_style', 'thumbnail');

  variable_set('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);
	user_role_grant_permissions(
		DRUPAL_AUTHENTICATED_RID, 
		_buildtapas_get_registered_user_permissions());

	echo "DEBUGGING: finished authenticated grant permissions
	";

/*
	_buildtapas_create_role(
		'paidmember',
		_tapas_get_paidmember_user_permissions(),
		3);
	
	_buildtapas_create_role(
		'siteeditor',
		_tbuildapas_get_siteeditor_user_permissions(),
		4);
*/

	$admin_permissions = array_keys(module_invoke_all('permission'));

	echo "DEBUGGING: Set admin_permissions array
	";

	$admin_role = _buildtapas_create_role('administrator', $admin_permissions,	 5);
  variable_set('user_admin_role', $admin_role->rid);
  db_insert('users_roles')
		->fields(array('uid' => 1, 'rid' => $admin_role->rid))
    ->execute();

	echo "DEBUGGING: completed do_user_settings routine.
	";

}


/**
 * Creates a role with the given name and permissions.
 */
function _buildtapas_create_role($rolename, $permissions, $weight) {

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

function _buildtapas_content_permissions_loop($types, $perms) {

	
	$result = array();

	foreach ($types as $type) {
		foreach ($perms as $perm) {
			$result[] = "$perm $type content";
		}
	}

	return $result;

}


/**
 * Return array of permissions for anonymous users
 */
function _buildtapas_get_anonymous_user_permissions() {

	return array(
		'access content',
		'access comments',
	);

}

/**
 * Return array of permissions for registered users
 */
function _buildtapas_get_registered_user_permissions() {

	$base =  array(
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
	);

	$content_perms = _buildtapas_content_permissions_loop(
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

	echo "DEBUGGING: base is " . var_dump($base) . " ####";
	echo "DEBUGGING: content is " .var_dump($content_perms) . " ####";

	$complete = array_merge(
		_buildtapas_get_anonymous_user_permissions(),
		$base,
		$content_perms);

	echo "DEBUGGING: complete is " . var_dump($complete) . " ####";

	buildtapas_check_permissions_array($complete);
	return $complete;

}

/**
 * Return an array of permissions for paid member users
 */
function _buildtapas_get_paidmember_user_permissions() {

	$base = array(
		'edit own comments',
		'use text format full_html',
		'change own username',
	);

	$tapas_content_perms = _buildtapas_content_permissions_loop(
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

	$general_content_perms = _buildtapas_content_permissions_loop(
		array(
			'tapasrecordnode'
		),
		array(
			'edit any',
			'delete any'
		)
	);

	$complete = array_merge(
		_buildtapas_get_registered_user_permissions(),
		$base,
		$tapas_content_perms,
		$general_content_perms);

	buildtapas_check_permissions_array($complete);

	return $complete;

}

/**
 * Return array of permissions for the site editor(s)
 */

function _buildtapas_get_siteeditor_user_permissions() {

	$base = array(
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
	);

	$content_perms = _buildtapas_content_permissions_loop(
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

	$complete = array_merge(
		_buildtapas_get_paidmember_user_permissions(),
		$base,
		$content_perms);

	buildtapas_check_permissions_array($complete);
	return $complete;
}
