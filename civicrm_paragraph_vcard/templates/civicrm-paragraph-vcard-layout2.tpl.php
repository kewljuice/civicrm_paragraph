<div class="contact-civicrm layout2">
    <div class="contact-item">
      <?php if ($contact['image_URL']): ?>
          <div class="contact-img-wrapper">
              <div class="contact-item-field contact-img">
                <?php
                $variables = [
                  'path' => $contact['image_URL'],
                  'alt' => 'image',
                  'width' => '150px',
                ];
                print theme('image', $variables);
                ?>
              </div>
          </div>
      <?php endif; ?>
        <div class="contact-info-wrapper">
          <?php if ($contact['display_name']): ?>
              <div class="contact-item-field contact-name">
                <?php print $contact['display_name']; ?>
              </div>
          <?php endif; ?>
          <?php if ($contact['job_title']): ?>
              <div class="contact-item-field contact-job-title">
                <?php print $contact['job_title']; ?>
              </div>
          <?php endif; ?>
          <?php if ($contact['current_employer']): ?>
              <div class="contact-item-field contact-current-employer">
                <?php print $contact['current_employer']; ?>
              </div>
          <?php endif; ?>
          <?php if ($contact['phone']): ?>
              <div class="contact-item-field contact-phone">
                <span class="label">
                  Tel:
                </span>
                  <a href="tel:<?php print $contact['phone']; ?>">
                    <?php print $contact['phone']; ?>
                  </a>
              </div>
          <?php endif; ?>
          <?php if ($contact['email']): ?>
              <div class="contact-item-field contact-email">
                  <a href="mailto:<?php print $contact['email']; ?>">
                    <?php print $contact['email']; ?>
                  </a>
              </div>
          <?php endif; ?>
        </div>
    </div>
</div>
