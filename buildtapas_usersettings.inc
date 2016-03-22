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

