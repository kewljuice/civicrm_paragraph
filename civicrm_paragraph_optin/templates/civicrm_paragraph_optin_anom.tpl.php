<div class="optin-civicrm">
    <div class="optin-item">
        <div class="optin-item-title">
          <?php print t('Subscribe to our newsletter'); ?>
        </div>
        <div class="optin-item-content">
          <?php
          $form = drupal_get_form('civicrm_paragraph_optin_anom_form', $object);
          print drupal_render($form);
          ?>
        </div>
    </div>
</div>