
Ikigai App — 8-Hour Hackathon Plan
Stack (pick before you start, don't debate it)
React + Vite PWA — runs in any browser, no app store, deploys in seconds to Vercel/Netlify. Looks native on mobile. Use Tailwind CSS for fast styling.

Optional: Expo React Native if you want it to feel truly native — but adds 30 min setup risk.

Team Split (4 people)
Person	Owns
A	App shell, navigation, design system, accessibility (font sizes, contrast, big buttons)
B	"How to Tech" screen
C	"Health" screen
D	"I'm Not Alone" screen + any backend (mock data is fine)
All work in the same repo. Person A unblocks everyone first with the shell.

Hour-by-Hour Timeline
Hour 0–1: Foundation (ALL TOGETHER)
Agree on colors, font sizes (min 20px body, 28px headings)
Person A scaffolds: npx create vite@latest ikigai -- --template react, installs Tailwind
Three-button home screen live and clickable by end of hour 1
Everyone else: wireframe their screen on paper
====================================================
Hour 1–4: Build in Parallel
====================================================
Person A — Shared components
=====================================================
BigButton, BackButton, SectionCard components
High contrast palette (dark text on cream/white, strong accent color)
Bottom nav or back arrow, large tap targets (min 48px)

=============================================================
Person B — "How to Tech"
===========================================================
Cards with big icons + short plain-English steps:

Card	                                       Content
Make text bigger	Step-by-step screenshots for iOS/Android font size
Avoid scams	        "If it says urgent, stop. Call a family member first." — 5 red flags
Video calls	        How to FaceTime/WhatsApp — embedded short YouTube
Bigger screen	    How to zoom in on phone
All static content — no backend needed.

======================================================================
Person C — "Health"
=========================================================================
Three cards:

Card	                                       Content
Train your brain	Embedded simple number memory game (build in 30 min) OR link to Lumosity
Gentle yoga	         Embedded YouTube: "chair yoga for seniors 10 min"
Daily movement	     Simple step goal tracker — just a counter button ("I moved today!") with a streak counter using localStorage
localStorage for streak = zero backend.

===============================================================
Person D — "I'm Not Alone"
=============================================================
Three sections:

Section	                            MVP(Minimum Viable Product)
Daily check-in	Button "Let my family know I'm ok" → sends WhatsApp/SMS link to pre-saved numbers (use sms: and https://wa.me/ URL scheme — no backend)
Meet nearby  	Mocked map with 3-4 fake "senior meetup" cards (coffee morning, walk group) — add Google Maps link to a real local spot
Chat with someone(maybe without it)	This is hard — options: (1) embed a Discord/Slack invite link to a moderated group, (2) show a mock chat UI for demo purposes, (3) link to a real platform like Befrienders
Be honest in demo: "check-in uses WhatsApp deep link, chat links to moderated community — backend would be v2"
=================================================
Hour 4–5: Integration
Merge all branches
Person A fixes any style inconsistencies
Everyone tests on actual phone (use your own phone + browser dev tools mobile view)
=========================================
Hour 5–6: Accessibility Pass
=========================================
Critical for this app — 30 min focused audit:

 All text ≥ 20px
 Buttons ≥ 48px tall
 No red/green only color coding (colorblindness)
 Every screen usable with one hand
 Test with phone screen reader on (VoiceOver/TalkBack) — even briefly

===========================================
Hour 6–7: Content + Polish
==============================================
Add real senior-friendly copy (no jargon, no small print)
Add a simple onboarding screen: "Enter family phone numbers" (saved to localStorage)
App icon, name, tagline on home screen
=================================================
Hour 7–8: Demo Prep
=================================================
Deploy to Vercel (vercel --prod — 2 minutes)
QR code on slide → judges scan and use it live
Prepare 3-minute pitch: problem → solution → demo → what's next
Home Screen Design

┌─────────────────────────┐
│   🌸  Ikigai             │
│   Your daily companion  │
│                         │
│  ┌───────────────────┐  │
│  │  📱 How to Tech   │  │  ← big, full-width cards
│  └───────────────────┘  │
│  ┌───────────────────┐  │
│  │  🌿 Health        │  │
│  └───────────────────┘  │
│  ┌───────────────────┐  │
│  │  🤝 I'm Not Alone │  │
│  └───────────────────┘  │
└─────────────────────────┘
What to Fake vs. Build Real
Feature	Real	Fake/Mock
Navigation	✅	
Tech guides	✅ static	
Health videos	✅ embedded	
Streak counter	✅ localStorage	
Family check-in	✅ WhatsApp link	
Nearby meetups	mock cards	backend map
Live chat		link to real platform
=============================================
Name options beyond "I'm Not Alone"
"My People" — warm, simple
"Together" — clear
=================================================
Winning the Demo
The judges will be moved if you show an elderly person's perspective. If you can, record a 30-second video of someone 60+ using it (parent, neighbor). That beats any slide.