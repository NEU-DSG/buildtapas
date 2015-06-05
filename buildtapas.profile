<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
	function system_form_install_configure_form_alter(&$form, $form_state) {
		$form['site_information']['site_name']['#default_value'] = 'buildtapas';
	}
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Select the current install profile by default.
 */

if (!function_exists("system_form_install_select_profile_form_alter")) {
	function system_form_install_select_profile_form_alter(&$form, $form_state) {
		foreach ($form['profile'] as $key => $element) {
			$form['profile'][$key]['#value'] = 'buildtapas';
		}
	}
}


/**
 * Activates site install hooks library
 */
//if (!function_exists('site_install_hooks_initialize')) {
//  require_once('libraries/site_install_hooks/site_install_hooks.inc');
//}
//site_install_hooks_initialize('buildtapas');
