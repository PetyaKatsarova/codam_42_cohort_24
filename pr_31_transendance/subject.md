This is a long group project. Poor early choices and lack of
team coordination will cost a lot of time. Your project and team
management will strongly impact your results. All team members must
actively participate and contribute to both the mandatory part and
the modules.

First, you will have to create a comprehensive README.md file. The detailed requirements
for the README are specified in the README Requirements section at the end of this
document.
Project Examples: Your project can take many forms. Here are some
valid examples:
• A multiplayer Pong game with tournament system
• A collaborative platform with real-time features
• A social network with user interactions
• An online game (Chess, Tic-Tac-Toe, etc.) with matchmaking
• A project management application
• Any other creative web application that meets the requirements
The key is to create something engaging that demonstrates your
technical skills and creativity.

Building an entire project is complicated, and many things can go wrong. To help you,
we will provide a list of general requirements that you must follow. If you don’t follow
them, your project will be rejected.
The requirements are the following:
• The project must be a web application, and requires a frontend, backend, and a
database.
• Git must be used with clear and meaningful commit messages. The repository must
show:
◦ Commits from all team members.
◦ Clear commit messages describing the changes.
◦ Proper work distribution across the team.
• Deployment must use a containerization solution (Docker, Podman, or equivalent) and run with a single command.
• Your website must be compatible with the latest stable version of Google Chrome.
• No warnings or errors should appear in the browser console.
• The project must include accessible Privacy Policy and Terms of Service pages
with relevant content.
Privacy Policy and Terms of Service: These pages will be verified
during evaluation. They must:
• Be easily accessible from the application (e.g., footer links).
• Contain relevant and appropriate content for your project.
• Not be placeholder or empty pages.
Missing or inadequate Privacy Policy/Terms of Service pages will
result in project rejection.
Multi-user Support (Mandatory): Your website must support multiple
users simultaneously. This is a core requirement of the project.
Users should be able to interact with the application at the same
time without conflicts or performance issues. This includes:
• Multiple users can be logged in and active at the same time.
• Concurrent actions by different users are handled properly.
• Real-time updates are reflected across all connected users when
applicable.
• No data corruption or race conditions occur with simultaneous
user actions.

 Technical requirements
This section, like the previous one, is mandatory. You will then be able to choose the
modules you want to use in the next chapter.
• A frontend that is clear, responsive, and accessible across all devices.
• Use a CSS framework or styling solution of your choice (e.g., Tailwind CSS,
Bootstrap, Material-UI, Styled Components, etc.).
• Store credentials (API keys, environment variables, etc.) in a local .env file that is
ignored by Git, and provide an .env.example file.
• The database must have a clear schema and well-defined relations.
• Your application must have a basic user management system. Users must be
able to sign up and log in securely:
◦ At minimum: email and password authentication with proper security (hashed
passwords, salted, etc.).
◦ Additional authentication methods (OAuth, 2FA, etc.) can be implemented
via modules.
• All forms and user inputs must be properly validated in both the frontend and
backend.
• For the backend, HTTPS must be used everywhere.
What is a Framework? For this project, a framework is defined as a
comprehensive tool that provides:
• A structured architecture and conventions for organizing code.
• Built-in features for common tasks (routing, state management,
etc.).
• A complete ecosystem of tools and libraries.
Examples:
• Frontend frameworks: React, Vue, Angular, Svelte, Next.js
(these are frameworks).
• Backend frameworks: Express, Fastify, NestJS, Django, Flask,
Ruby on Rails.
• Not frameworks: jQuery (library), Lodash (utility library),
Axios (HTTP client).
Note: React is considered a framework in this context due to its
ecosystem and architectural patterns, even though it is technically a
library.

**Modules
You will need to earn 14 points in total to complete your project. Each major module
is worth 2 points, and each minor module is worth 1 point.
The following categories are available. You may choose multiple modules from any category:
• Web
• Accessibility and Internationalization
• User Management
• Artificial Intelligence
• Cybersecurity
• Gaming and user experience
• Devops
• Data and Analytics
• Blockchain
• Modules of choice
We strongly recommend choosing modules only after your ideas are clear and you have
a good understanding of what you want to build.
Additionally, aiming for more than 14 points in total may be a good idea, especially if
some modules aren’t validated during the evaluation.

Important - Module Dependencies and Evaluation:
• Some modules require other modules to be implemented first
(marked with info notes).
• Gaming modules (AI Opponent, Tournament, Game customization,
Spectator mode, Multiplayer 3+, Add another game) require that
at least one game be implemented first.
• The Game Statistics module requires that a game be implemented.
• Advanced chat features require the basic chat functionality
from the "User interaction" module.
• SSR is incompatible with the ICP blockchain backend.
• Plan your modules carefully to ensure they work together
coherently!
• During evaluation: You will be asked to demonstrate
each claimed module. Only fully functional and properly
implemented modules will be counted toward your final score.
Non-functional or incomplete modules = 0 points.
-----------------------------------------------------
**Web**
• Major: Use a framework for both the frontend and backend.
◦ Use a frontend framework (React, Vue, Angular, Svelte, etc.).
◦ Use a backend framework (Express, NestJS, Django, Flask, Ruby on Rails,
etc.).
◦ Full-stack frameworks (Next.js, Nuxt.js, SvelteKit) count as both if you use
both their frontend and backend capabilities.
• Minor: Use a frontend framework (React, Vue, Angular, Svelte, etc.).
• Minor: Use a backend framework (Express, Fastify, NestJS, Django, etc.).
• Major: Implement real-time features using WebSockets or similar technology.
◦ Real-time updates across clients.
◦ Handle connection/disconnection gracefully.
◦ Efficient message broadcasting.
• Major: Allow users to interact with other users. The minimum requirements are:
◦ A basic chat system (send/receive messages between users).
◦ A profile system (view user information).
◦ A friends system (add/remove friends, see friends list).
• Major: A public API to interact with the database with a secured API key, rate
limiting, documentation, and at least 5 endpoints:
◦ GET /api/{something}
◦ POST /api/{something}
◦ PUT /api/{something}
◦ DELETE /api/{something}
• Minor: Use an ORM for the database.
• Minor: A complete notification system for all creation, update, and deletion actions.
• Minor: Real-time collaborative features (shared workspaces, live editing, collaborative drawing, etc.).
• Minor: Server-Side Rendering (SSR) for improved performance and SEO.
• Minor: Progressive Web App (PWA) with offline support and installability.
• Minor: Custom-made design system with reusable components, including a proper
color palette, typography, and icons (minimum: 10 reusable components).
12
ft_transcendence Surprise.
• Minor: Implement advanced search functionality with filters, sorting, and pagination.
• Minor: File upload and management system.
◦ Support multiple file types (images, documents, etc.).
◦ Client-side and server-side validation (type, size, format).
◦ Secure file storage with proper access control.
◦ File preview functionality where applicable.
◦ Progress indicators for uploads.
◦ Ability to delete uploaded files.
-----------------------------------------------------

**Accessibility and Internationalization**
• Major: Complete accessibility compliance (WCAG 2.1 AA) with screen reader
support, keyboard navigation, and assistive technologies.
• Minor: Support for multiple languages (at least 3 languages).
◦ Implement i18n (internationalization) system.
◦ At least 3 complete language translations.
◦ Language switcher in the UI.
◦ All user-facing text must be translatable.
• Minor: Right-to-left (RTL) language support.
◦ Support for at least one RTL language (Arabic, Hebrew, etc.).
◦ Complete layout mirroring (not just text direction).
◦ RTL-specific UI adjustments where needed.
◦ Seamless switching between LTR and RTL.
• Minor: Support for additional browsers.
◦ Full compatibility with at least 2 additional browsers (Firefox, Safari, Edge,
etc.).
◦ Test and fix all features in each browser.
◦ Document any browser-specific limitations.
◦ Consistent UI/UX across all supported browsers.
------------------------------------------------------

**User Management**
• Major: Standard user management and authentication.
◦ Users can update their profile information.
◦ Users can upload an avatar (with a default avatar if none provided).
◦ Users can add other users as friends and see their online status.
◦ Users have a profile page displaying their information.
• Minor: Game statistics and match history (requires a game module).
◦ Track user game statistics (wins, losses, ranking, level, etc.).
◦ Display match history (1v1 games, dates, results, opponents).
◦ Show achievements and progression.
◦ Leaderboard integration.
This module requires you to have implemented at least one game (see
"Gaming and user experience" section). You cannot claim this module
without a functional game.
• Minor: Implement remote authentication with OAuth 2.0 (Google, GitHub, 42,
etc.).
• Major: Advanced permissions system:
◦ View, edit, and delete users (CRUD).
◦ Roles management (admin, user, guest, moderator, etc.).
◦ Different views and actions based on user role.
• Major: An organization system:
◦ Create, edit, and delete organizations.
◦ Add users to organizations.
◦ Remove users from organizations.
◦ View organizations and allow users to perform specific actions within an organization (minimum: create, read, update).
• Minor: Implement a complete 2FA (Two-Factor Authentication) system for the
users.
• Minor: User activity analytics and insights dashboard.
--------------------------------------------------------

**Artificial Intelligence**
• Major: Introduce an AI Opponent for games.
◦ The AI must be challenging and able to win occasionally.
◦ The AI should simulate human-like behavior (not perfect play).
◦ If you implement game customization options, the AI must be able to use
them.
◦ You must be able to explain your AI implementation during evaluation.
This module requires you to have implemented at least one game (see
"Gaming and user experience" section). The AI must be able to play
your game competently.
• Major: Implement a complete RAG (Retrieval-Augmented Generation) system.
◦ Interact with a large dataset of information.
◦ Users can ask questions and get relevant answers.
◦ Implement proper context retrieval and response generation.
• Major: Implement a complete LLM system interface.
◦ Generate text and/or images based on user input.
◦ Handle streaming responses properly.
◦ Implement error handling and rate limiting.
• Major: Recommendation system using machine learning.
◦ Personalized recommendations based on user behavior.
◦ Collaborative filtering or content-based filtering.
◦ Continuously improve recommendations over time.
• Minor: Content moderation AI (auto moderation, auto deletion, auto warning,
etc.)
• Minor: Voice/speech integration for accessibility or interaction.
• Minor: Sentiment analysis for user-generated content.
• Minor: Image recognition and tagging system.
---------------------------------------------------------

**Cybersecurity**
• Major: Implement WAF/ModSecurity (hardened) + HashiCorp Vault for secrets:
◦ Configure strict ModSecurity/WAF.
◦ Manage secrets in Vault (API keys, credentials, environment variables), encrypted and isolated.
IV.6 Gaming and user experience
• Major: Implement a complete web-based game where users can play against each
other.
◦ The game can be real-time multiplayer (e.g., Pong, Chess, Tic-Tac-Toe, Card
games, etc.).
◦ Players must be able to play live matches.
◦ The game must have clear rules and win/loss conditions.
◦ The game can be 2D or 3D.
• Major: Remote players — Enable two players on separate computers to play the
same game in real-time.
◦ Handle network latency and disconnections gracefully.
◦ Provide a smooth user experience for remote gameplay.
◦ Implement reconnection logic.
• Major: Multiplayer game (more than two players).
◦ Support for three or more players simultaneously.
◦ Fair gameplay mechanics for all participants.
◦ Proper synchronization across all clients.
This module requires you to have implemented at least one game (see
"Gaming and user experience" section). You’re extending your game to
support three or more players.
• Major: Add another game with user history and matchmaking.
◦ Implement a second distinct game.
◦ Track user history and statistics for this game.
◦ Implement a matchmaking system.
◦ Maintain performance and responsiveness.
16
ft_transcendence Surprise.
This module requires you to have already implemented a first game
(see "Implement a complete web-based game" module above). You cannot
claim this module without having a functional first game.
• Major: Implement advanced 3D graphics using a library like Three.js or Babylon.js.
◦ Create an immersive 3D environment.
◦ Implement advanced rendering techniques.
◦ Ensure smooth performance and user interaction.
• Minor: Advanced chat features (enhances the basic chat from "User interaction"
module).
◦ Ability to block users from messaging you.
◦ Invite users to play games directly from chat.
◦ Game/tournament notifications in chat.
◦ Access to user profiles from chat interface.
◦ Chat history persistence.
◦ Typing indicators and read receipts.
This module enhances the basic chat system from the "Allow users
to interact" module. You cannot claim this module without having
implemented the basic chat first.
• Minor: Implement a tournament system.
◦ Clear matchup order and bracket system.
◦ Track who plays against whom.
◦ Matchmaking system for tournament participants.
◦ Tournament registration and management.
This module requires you to have implemented at least one game (see
"Gaming and user experience" section). You cannot have tournaments
without a game to play.
• Minor: Game customization options.
◦ Power-ups, attacks, or special abilities.
17
ft_transcendence Surprise.
◦ Different maps or themes.
◦ Customizable game settings.
◦ Default options must be available.
This module requires you to have implemented at least one game (see
"Gaming and user experience" section). You’re adding customization
to an existing game.
• Minor: A gamification system to reward users for their actions.
◦ Implement at least 3 of the following: achievements, badges, leaderboards,
XP/level system, daily challenges, rewards
◦ System must be persistent (stored in database)
◦ Visual feedback for users (notifications, progress bars, etc.)
◦ Clear rules and progression mechanics
While this is a Minor module (1 point), implementing a complete
gamification system can be substantial. Focus on quality over
quantity—three well-implemented features are better than six poorly
done ones.
• Minor: Implement spectator mode for games.
◦ Allow users to watch ongoing games.
◦ Real-time updates for spectators.
◦ Optional: spectator chat.
This module requires you to have implemented at least one game (see
"Gaming and user experience" section). Spectators need a game to
watch.
-------------------------------------------------

**Data and Analytics**
• Major: Advanced analytics dashboard with data visualization.
◦ Interactive charts and graphs (line, bar, pie, etc.).
◦ Real-time data updates.
◦ Export functionality (PDF, CSV, etc.).
◦ Customizable date ranges and filters.
• Minor: Data export and import functionality.
◦ Export data in multiple formats (JSON, CSV, XML, etc.).
◦ Import data with validation.
◦ Bulk operations support.
• Minor: GDPR compliance features.
◦ Allow users to request their data.
◦ Data deletion with confirmation.
◦ Export user data in a readable format.
◦ Confirmation emails for data operations.
------------------------------------------------

Social and Collaborative Projects
These projects emphasize user interaction and community building:
• Social Network: User profiles, posts, comments, likes, friends, real-time chat, and notifications.
◦ Suggested modules: User interaction, Real-time features, Notification system,
Advanced chat, File upload
◦ Point potential: 14+ points
• Collaborative Workspace: Real-time document editing, project management,
team chat, and file sharing.
◦ Suggested modules: Real-time collaborative features, User interaction, Organization system, File upload, Advanced permissions
◦ Point potential: 15+ points
• Forum Platform: Discussion boards with categories, threads, moderation tools,
and user reputation systems.
22
ft_transcendence Surprise.
◦ Suggested modules: User interaction, Advanced permissions, Gamification,
Content moderation AI, Advanced search
◦ Point potential: 14+ points
• Event Management Platform: Create and manage events, RSVP system, calendar integration, and notifications.
◦ Suggested modules: User interaction, Notification system, Organization system, Public API, Advanced search
◦ Point potential: 14+ points
• Learning Management System: Courses, assignments, quizzes, progress tracking, and student-teacher interaction.
◦ Suggested modules: User interaction, Organization system, Advanced permissions, File upload, Analytics dashboard
◦ Point potential: 15+ points
--------------------------------------------------

**Creative and Media Projects**
These projects focus on content creation and sharing:
• Music Streaming Platform: Upload and stream music, playlists, recommendations, and social features.
◦ Suggested modules: File upload, User interaction, Recommendation system,
Advanced search, Analytics dashboard
◦ Point potential: 15+ points
• Video Sharing Platform: Upload and watch videos, comments, likes, subscriptions, and recommendations.
◦ Suggested modules: File upload, User interaction, Recommendation system,
Content moderation AI, Advanced search
◦ Point potential: 16+ points
• Art Gallery: Share artwork in galleries, with comments, likes, and artist profiles.
◦ Suggested modules: File upload, User interaction, Image recognition, Advanced
search, Custom design system
◦ Point potential: 14+ points
• Blogging Platform: Create and publish blogs, with comments, tags, categories,
and reader engagement.
◦ Suggested modules: User interaction, SSR, Advanced search, Sentiment analysis, Multiple languages
◦ Point potential: 14+ points
23
ft_transcendence Surprise.
• Recipe Sharing Platform: Share recipes, ratings, comments, meal planning, and
shopping lists.
◦ Suggested modules: User interaction, File upload, Advanced search, Recommendation system, PWA
◦ Point potential: 14+ points
---------------------------------------------------------

**Productivity and Tools Projects** NB->US
These projects help users organize and manage their work:
• Task Management System: Projects, tasks, assignments, deadlines, team collaboration, and progress tracking.
◦ Suggested modules: Organization system, User interaction, Real-time collaborative features, Notification system, Analytics dashboard
◦ Point potential: 15+ points
----------------------------------------------------------

• **Code Collaboration Platform**: Share code snippets, collaborative coding, version control, and discussions.
◦ Suggested modules: User interaction, Real-time collaborative features, Public
API, Advanced search, Custom design system
◦ Point potential: 14+ points
• Booking System: Reserve resources (rooms, equipment, appointments), calendar,
and notifications.
◦ Suggested modules: User interaction, Organization system, Notification system, Public API, Advanced search
◦ Point potential: 14+ points
• Marketplace Platform: Buy and sell items, with user ratings, messaging, payment integration, and search functionality.
◦ Suggested modules: User interaction, File upload, Advanced search, Recommendation system, Public API
◦ Point potential: 14+ points
• Fitness Tracker: Log workouts, track progress, challenges, leaderboards, and
social features.
◦ Suggested modules: User interaction, Gamification, Analytics dashboard, PWA,
Data export/import
◦ Point potential: 14+ points
------------------------------------------------------------

These are just ideas to inspire you. The key is to choose a project
that:
• Interests your team and motivates everyone to work on it.
• Allows you to implement the required modules (14 points
minimum).
• Demonstrates technical complexity and creativity.
• Can be realistically completed within the project timeline.
• Has coherent module combinations that work well together.
Discuss with your team, review the available modules, and choose
wisely!
------------------------------------------------------------
**Readme Requirements**
A README.md file must be provided at the root of your Git repository. Its purpose is
to allow anyone unfamiliar with the project (peers, staff, recruiters, etc.) to quickly
understand what the project is about, how to run it, and where to find more information
on the topic.
The README.md must include at least:
• The very first line must be italicized and read: This project has been created as part
of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].
• A “Description” section that clearly presents the project, including its goal and a
brief overview.
• An “Instructions” section containing any relevant information about compilation,
installation, and/or execution.
• A “Resources” section listing classic references related to the topic (documentation, articles, tutorials, etc.), as well as a description of how AI was used —
specifying for which tasks and which parts of the project.
➠ Additional sections may be required depending on the project (e.g., usage
examples, feature list, technical choices, etc.).
Any required additions will be explicitly listed below.
• The “Description” section should also contain a clear name for the project and its
key features.
• The “Instructions” section should mention all the needed prerequisites (software,
tools, versions, configuration like .env setup, etc.), and step-by-step instructions to
run the project.
Additional sections required for this activity:
• Team Information:
For each team member mentioned at the top of the README.md, you must provide:
27
ft_transcendence Surprise.
◦ Assigned role(s): PO, PM, Tech Lead, Developers, etc.
◦ Brief description of their responsibilities.
• Project Management:
◦ How the team organized the work (task distribution, meetings, etc.).
◦ Tools used for project management (GitHub Issues, Trello, etc.).
◦ Communication channels used (Discord, Slack, etc.).
• Technical Stack:
◦ Frontend technologies and frameworks used.
◦ Backend technologies and frameworks used.
◦ Database system and why it was chosen.
◦ Any other significant technologies or libraries.
◦ Justification for major technical choices.
• Database Schema:
◦ Visual representation or description of the database structure.
◦ Tables/collections and their relationships.
◦ Key fields and data types.
• Features List:
◦ Complete list of implemented features.
◦ Which team member(s) worked on each feature.
◦ Brief description of each feature’s functionality.
• Modules:
◦ List of all chosen modules (Major and Minor).
◦ Point calculation (Major = 2pts, Minor = 1pt).
◦ Justification for each module choice, especially for custom "Modules of
choice".
◦ How each module was implemented.
◦ Which team member(s) worked on each module.
• Individual Contributions:
◦ Detailed breakdown of what each team member contributed.
◦ Specific features, modules, or components implemented by each person.
◦ Any challenges faced and how they were overcome.
28
ft_transcendence Surprise.
Any other useful or relevant information is welcome (usage documentation, known
limitations, license, credits, etc.).
The README.md is a critical part of your project evaluation. It
should be:
• Clear and well-organized.
• Complete with all required sections.
• Professional and easy to read.
• Honest about contributions and challenges.
A poor or incomplete README can negatively impact your evaluation.
-------------------------------------------------------------

**Bonus part**
The bonus part will be considered only if all required modules have been implemented
corresponding to the minimum of 14 mandatory points.
Each additional module implemented beyond the required 14 points may be considered
as a bonus.
For each extra module:
• It must be fully functional
• It must meet the module requirements description
• It must add real value to the project
• It must include a proper justification in the README
Each validated extra module will be taken into account during the review as follows:
• Major modules: 2 points each
• Minor modules: 1 point each
You can have a maximum of 5 points (e.g., 5 minor modules, or 2 major modules + 1
minor module)
---------------------------------------------------------------

We highly recommend that you discuss your ideas with your team and peers before
starting to work on the project.
During the evaluation, a brief modification of the project may occasionally be requested. This could involve a minor behavior change, a few lines of code to write or
rewrite, or an easy-to-add feature.
While this step may not be applicable to every project, you must be prepared for it
if it is mentioned in the evaluation guidelines.
This step is meant to verify your actual understanding of a specific part of the project.
The modification can be performed in any development environment you choose (e.g.,
your usual setup), and it should be feasible within a few minutes — unless a specific
timeframe is defined as part of the evaluation.
You can, for example, be asked to make a small update to a function or script, modify a
display, or adjust a data structure to store new information, etc.
The details (scope, target, etc.) will be specified in the evaluation guidelines and may
vary from one evaluation to another for the same project.






































