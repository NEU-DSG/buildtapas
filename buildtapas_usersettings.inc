<?php
/**
 * @file
 *
 * Contains portions of the install related to user permissions.
 *
 * Note that permissions specific to the tapas content types (Project,
 * Collection, and TEI Record) are set in the tapas_modules/tapascontent
 * module, rather than here.
 */

//@TODO: Set these constants up in a single, accessible place rather than...
// having to declare them separately here and in the tapascontent module.

/** Name of paid-member role. Must match any modules that access it. */
define ('TAPAS_PAIDMEMBER_ROLE', 'paidmember');
/** Name of admin role. Must match any modules that access it. */
define ('TAPAS_ADMIN_ROLE', 'administrator');


/**
 * Check for unrecognized permissions.
 *
 * Drupal will blow up if you try to pass it unrecognized
 * permission strings in certain functions, so this function
 * will allow us to "fail fast" and with a clear error message,
 * rather than slowly with a cryptic one.
 */
function buildtapas_check_permissions_array($perms) {

	$all_perms = array_keys(user_permission_get_modules());
	$err_check = array_diff($perms, $all_perms);

	if ($err_check) {
		echo "
		################################
		found unrecognized permissions:
		--------------------------------
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
}



/**
 *	Set up user settings and permissions.
 */
function buildtapas_do_user_settings() {

	user_role_grant_permissions(
		DRUPAL_ANONYMOUS_RID,
		_buildtapas_get_anonymous_user_permissions());

  variable_set('user_pictures', '1');
  variable_set('user_picture_dimensions', '1024x1024');
  variable_set('user_picture_file_size', '800');
  variable_set('user_picture_style', 'thumbnail');

  variable_set('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);
	user_role_grant_permissions(
		DRUPAL_AUTHENTICATED_RID, 
		_buildtapas_get_registered_user_permissions()
	);

	_buildtapas_create_role(
		TAPAS_PAIDMEMBER_ROLE,
		_buildtapas_get_paidmember_user_permissions(),
		3
	);
	
	$admin_permissions = array_keys(module_invoke_all('permission'));

	$admin_role = _buildtapas_create_role(TAPAS_ADMIN_ROLE, $admin_permissions,	 5);
  variable_set('user_admin_role', $admin_role->rid);
  db_insert('users_roles')
		->fields(array('uid' => 1, 'rid' => $admin_role->rid))
    ->execute();

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

	$registered_perms =  array(
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
		'access user profiles',
		'cancel account',
		'create forum content',
		'edit own forum content',
		'delete own forum content',
	);

	$complete = array_merge(
		_buildtapas_get_anonymous_user_permissions(),
		$registered_perms);

	buildtapas_check_permissions_array($complete);
	return $complete;

}

/**
 * Return an array of permissions for paid member users
 */
function _buildtapas_get_paidmember_user_permissions() {

	// The majority of paid user perks relate to permissions
	// handled in the tapas_modules/tapascontent module, rather than here.

	$paid_perms = array(
		'edit own comments',
		'use text format full_html',
		'change own username',
	);

	$complete = array_merge(
		_buildtapas_get_registered_user_permissions(),
		$paid_perms);

	buildtapas_check_permissions_array($complete);

	return $complete;

}

