<div class="optin-civicrm">
    <div class="optin-item">
        <div class="optin-item-title">
          <?php print t('Manage your newsletter subscriptions'); ?>
        </div>
        <div class="optin-item-content">
          <?php print drupal_render(drupal_get_form('civicrm_paragraph_optin_form', $object)); ?>
        </div>
    </div>
</div>
