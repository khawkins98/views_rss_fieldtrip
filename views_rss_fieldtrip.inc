<?php

/**
 * @file
 * Preprocess functions for Views RSS: Field Trip module.
 */

/**
 * Preprocess function for item <fieldtrip:image> element.
 */
function views_rss_fieldtrip_preprocess_item_image(&$variables) {
  // No value = no preprocessing.
  if (empty($variables['elements'][0]['value'])) {
    return;
  }
  if (!empty($variables['raw'])) {
    $value = array();
    foreach ($variables['raw'] as $delta => $element) {
      if (!empty($element['rendered']['#rss_element'])) {
        $value[] = $element['rendered']['#rss_element'];
      }
    }
    $variables['elements'] = $value;
  }
}

/**
 * Preprocess function for item <fieldtrip:image_attribution> element.
 */
function views_rss_fieldtrip_preprocess_item_image_attribution(&$variables) {
  // We won't use this here, we'll embed it with the image value later.
  //if (empty($variables['elements'][0]['value'])) {
    $value[] = '';
    //return;
  //}
/*  if (!empty($variables['raw'])) {
    $value = array();
    foreach ($variables['raw'] as $delta => $element) {
      if (!empty($element['rendered']['#rss_element'])) {
        $value[] = $element['rendered']['#rss_element'];
      }
    }
    $variables['elements'] = $value;
  }*/
}

/**
 * Preprocess function for item <fieldtrip:image_title> element.
 */
function views_rss_fieldtrip_preprocess_item_image_title(&$variables) {
  // We won't use this here, we'll embed it with the image value later.
  $value[] = '';
  //return;
}
