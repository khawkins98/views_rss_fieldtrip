About Views RSS Fieldtrip
=========================

This is a very simple module that provides some features to help integrate Drupal RSS with custom elements required by Google Field Trip.

Not all elements are implemented as I've only done the ones I need, but this module can be easily modified to support other fields as speced at http://www.fieldtripper.com/fieldtrip_rss

Requirements
------------

This module requires Drupal RSS to be enabled.

Limitations
-----------

This module was done to fix a small need and not done with a full GUI config. To repurpose for other sites you'll need to:

- To support offset=0&limit=50 you'll need to specify your view name in hook_views_pre_build
- Image title and attribution are hard coded to our nomencalture in hook_field_formatter_view

If there is demand for this module, let me know and I'll polish.

Credit
------
Thanks to these two sources for some getting started info:

- http://www.phase2technology.com/blog/your-guide-to-extending-rss-feeds-in-drupal/
- https://drupal.org/node/1346506

And a thanks to the MediaRSS module for helpf figuring out the subelement structure (and code reuse).

About the Developer
-------------------

This project is not really maintained and was done one off for the hyperlocal community news website, TheDigitel.com It was thrown together by Ken Hawkins ( AllAboutKen.com / @khawkins98 ). The latest code should be at GitHub ( https://github.com/khawkins98 )