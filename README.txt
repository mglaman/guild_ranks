=====
Guild Rank
https://github.com/mglaman/guild_ranks
-----
This module allows you to select a taxonomy term reference field attached to user accounts and relate them to a user role. As of now there is no easy way to weight user roles. This module provides a way for Drupal sites with multiple ranks (like a guild or clan) and assign them to specific roles.

You can also define a super admin role that will not be overwritten. That way you can designate a user as an administrator of the site without changing that user's rank. The role of anonymous user has been removed from this selection. Shares same array as relationship area, need to make a separate array to remove that as well for security.

Not completely tested, but does work.

=====
Installation
-----

1. Enable the module
2. Visit ?q=admin/config/guild/ranks
3. Select a user taxonomy reference field (detects automatically which you can choose)
4. Select a super admin role
5. Save form
6. Create your taxonomy to role relationships.
