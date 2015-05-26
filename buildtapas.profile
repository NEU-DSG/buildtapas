<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function buildtapas_form_install_configure_form_alter(&$form, $form_state) {
	if (!function_exists("system_form_install_configure_form_alter")) {
		function system_form_install_configure_form_alter(&$form, $form_state) {
			$form['site_information']['site_name']['#default_value'] = 'buildtapas';
		}
	}
}

/**
 * Implements hook_form_alter().
 *
 * Select the current install profile by default.
 */

function buildtapas_form_alter(&$form, $form_state) {
	if (!function_exists("system_form_install_select_profile_form_alter")) {
		function system_form_install_select_profile_form_alter(&$form, $form_state) {
			foreach ($form['profile'] as $key => $element) {
				$form['profile'][$key]['#value'] = 'buildtapas';
			}
		}
	}
}
