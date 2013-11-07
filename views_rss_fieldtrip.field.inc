<?php

/**
 * Implements hook_field_formatter_info().
 */
function views_rss_fieldtrip_field_formatter_info() {
  $formatters = array(
    'fieldtrip_image' => array(
      'label' => t('RSS <fieldtrip:image> element'),
      'field types' => array('image', 'file'),
      'settings' => array(
        'image_style' => '',
        'group_multiple_values' => 0,
        'medium' => '',
        'expression' => '',
        'generate_hash' => 0,
        'hash_algo' => 'md5',
      ),
    ),
  );
  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function views_rss_fieldtrip_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  if ($display['type'] == 'fieldtrip_image') {

    $element['group_multiple_values'] = array(
      '#title' => t('Group multiple field values in one &lt;fieldtrip:group&gt; element'),
      '#type' => 'checkbox',
      '#default_value' => $settings['group_multiple_values'],
      '#description' => t('&lt;fieldtrip:image&gt; THIS NEEDS WORK. !more_link', array(
        '!more_link' => l('[?]', 'http://www.rssboard.org/media-rss#media-group', array('attributes' => array('title' => t('Need more information?')))),
      )),
    );

  }

  return $element;
}



/**
 * Implements hook_field_formatter_settings_summary().
 */
function views_rss_fieldtrip_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  if ($field['type'] == 'image') {
    $image_styles = image_style_options(FALSE);
    // Unset possible 'No defined styles' option.
    unset($image_styles['']);
    // Styles could be lost because of enabled/disabled modules that defines
    // their styles in code.
    if (isset($settings['image_style']) && isset($image_styles[$settings['image_style']])) {
      $summary[] = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
    }
    else {
      $summary[] = t('Original image');
    }
  }

  if ($display['type'] == 'fieldtrip_image') {

    if (!empty($display['settings']['group_multiple_values'])) {
      $summary[] = t('Group multiple values');
    }

    $value = (!empty($display['settings']['medium'])) ? $display['settings']['medium'] : t('none');
    $summary[] = t('Medium: !medium', array('!medium' => $value));

  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function views_rss_fieldtrip_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {

    if ($display['type'] == 'fieldtrip_image') {

      // Inside a view item may contain NULL data. In that case, just return.
      if (empty($item['fid'])) {
        unset($items[$delta]);
        continue;
      }

      // Default file URL.
      $item_uri = $item['uri'];
      $url = file_create_url($item_uri);

      // For images provide styled image URL if required.
      if (!empty($display['settings']['image_style']) && $image_style = image_style_load($display['settings']['image_style'])) {
        // Get full image URI based on provided image style.
        $url = image_style_url($display['settings']['image_style'], $item_uri);
        // Make sure that image style file has already been created.
        $path = image_style_path($display['settings']['image_style'], $item_uri);
        if (!file_exists(drupal_realpath($path))) {
          image_style_create_derivative($image_style, $item_uri, $path);
        }
        $item_uri = $path;
      }

    }

    if ($display['type'] == 'fieldtrip_image') {

      $rss_element = array(
        'key' => 'fieldtrip:image',
        'attributes' => array(
          //'url' => $url,
          //'fileSize' => $item['filesize'],
          //'type' => $item['filemime'],
        ),
      );

      // Additional properties for images.
      if ($item['type'] == 'image') {
        $media_info = image_load($item_uri);
        if (!empty($media_info)) {
          //$item['info'] = $media_info;
          //$rss_element['attributes']['width'] = $media_info->info['width'];
          //$rss_element['attributes']['height'] = $media_info->info['height'];
        }
      }

      // Other additional sub-elements.
      $extra_fields = array('title', 'description');

      $count = -1;
      foreach ($extra_fields as $extra_field) {
        $count++;
        $subelement = array();
        $field_extra_field = 'field_' . $extra_field;
        // Images could have 'title' and 'description' properties.
        if (isset($item[$extra_field]) && $item[$extra_field]) {
          $subelement = array(
            'key' => 'fieldtrip:' . $extra_field,
            'value' => $item[$extra_field],
          );
        }

        /*
        $subelement = array(
          'key' => 'url',
          'value' => $url,
        );
        */

        if ($url) {
          $rss_element['value']['url'] = $url;
          $rss_element['value']['title'] = $items[$count]['field_file_image_title_text']['und'][0]['safe_value'];
          $rss_element['value']['attribution'] = $items[$count]['field_credit_w_link']['und'][0]['title'];
        }


      }

    }


    $element[$delta] = array(
      '#item' => $item,
      '#markup' => format_xml_elements(array($rss_element)),
      '#rss_element' => $rss_element,
      '#settings' => $display['settings'],
    );

  }

  return $element;
}
