Add Multilanguage in ~30 Minutes
Install the library

npm install react-i18next i18next i18next-browser-languagedetector
File Structure
Create this in your src/ folder:

NB!!: replace not allone with "together"
src/
  locales/
    en.json
    nl.json
    es.json
    bg.json
  i18n.js
Translation Files
src/locales/en.json:


{
  "home": {
    "title": "Ikigai",
    "subtitle": "Your daily companion",
    "tech": "📱 How to Tech",
    "health": "🌿 Health",
    "notAlone": "🤝 I'm Not Alone"
  },
  "tech": {
    "title": "How to Tech",
    "biggerText": "Make Text Bigger",
    "avoidScams": "Avoid Scams",
    "videoCalls": "Video Calls"
  },
  "health": {
    "title": "Health",
    "brain": "Train Your Brain",
    "yoga": "Gentle Yoga",
    "move": "Move Today"
  },
  "notAlone": {
    "title": "I'm Not Alone",
    "checkIn": "Let family know I'm okay",
    "meet": "Meet people nearby",
    "chat": "Chat with someone"
  }
}
src/locales/nl.json:


{
  "home": {
    "title": "Ikigai",
    "subtitle": "Jouw dagelijkse metgezel",
    "tech": "📱 Hoe gebruik ik technologie",
    "health": "🌿 Gezondheid",
    "notAlone": "🤝 Ik ben niet alleen"
  },
  "tech": {
    "title": "Technologie hulp",
    "biggerText": "Tekst groter maken",
    "avoidScams": "Oplichting vermijden",
    "videoCalls": "Videobellen"
  },
  "health": {
    "title": "Gezondheid",
    "brain": "Train je hersenen",
    "yoga": "Zachte yoga",
    "move": "Beweeg vandaag"
  },
  "notAlone": {
    "title": "Ik ben niet alleen",
    "checkIn": "Laat familie weten dat ik goed ben",
    "meet": "Ontmoet mensen in de buurt",
    "chat": "Chat met iemand"
  }
}
src/locales/es.json:


{
  "home": {
    "title": "Ikigai",
    "subtitle": "Tu compañero diario",
    "tech": "📱 Cómo usar la tecnología",
    "health": "🌿 Salud",
    "notAlone": "🤝 No estoy solo/a"
  },
  "health": {
    "title": "Salud",
    "brain": "Entrena tu mente",
    "yoga": "Yoga suave",
    "move": "Muévete hoy"
  },
  "notAlone": {
    "title": "No estoy solo/a",
    "checkIn": "Avisar a mi familia que estoy bien",
    "meet": "Conocer gente cercana",
    "chat": "Chatear con alguien"
  }
}
src/locales/bg.json:


{
  "home": {
    "title": "Икигай",
    "subtitle": "Вашият ежедневен спътник",
    "tech": "📱 Как да използвам телефона",
    "health": "🌿 Здраве",
    "notAlone": "🤝 Не съм сам/а"
  },
  "health": {
    "title": "Здраве",
    "brain": "Трениране на ума",
    "yoga": "Лека йога",
    "move": "Движение днес"
  },
  "notAlone": {
    "title": "Не съм сам/а",
    "checkIn": "Уведоми семейството ми",
    "meet": "Срещни хора наблизо",
    "chat": "Разговор с някого"
  }
}
Setup File
src/i18n.js:


import i18n from 'i18next'
import { initReactI18next } from 'react-i18next'
import LanguageDetector from 'i18next-browser-languagedetector'

import en from './locales/en.json'
import nl from './locales/nl.json'
import es from './locales/es.json'
import bg from './locales/bg.json'

i18n
  .use(LanguageDetector)       // auto-detects browser language
  .use(initReactI18next)
  .init({
    resources: { en: { translation: en }, nl: { translation: nl },
                 es: { translation: es }, bg: { translation: bg } },
    fallbackLng: 'en',         // if language missing, use English
    interpolation: { escapeValue: false }
  })

export default i18n
Import it once at the top of src/main.jsx:


import './i18n'   // ← add this line, before App import
import App from './App'
Using Translations in Components

import { useTranslation } from 'react-i18next'

function Home() {
  const { t } = useTranslation()

  return (
    <div className="flex flex-col gap-4 p-6">
      <h1 className="text-4xl font-bold text-center">{t('home.title')}</h1>
      <p className="text-xl text-center text-gray-600">{t('home.subtitle')}</p>

      <BigButton label={t('home.tech')}     onClick={() => navigate('/tech')} />
      <BigButton label={t('home.health')}   onClick={() => navigate('/health')} />
      <BigButton label={t('home.notAlone')} onClick={() => navigate('/not-alone')} />
    </div>
  )
}
Replace every hardcoded string with t('key'). That's it.

Language Switcher Component
Make this big and obvious — elderly users need to find it easily:

src/components/LanguageSwitcher.jsx:


import { useTranslation } from 'react-i18next'

const languages = [
  { code: 'en', label: 'English', flag: '🇬🇧' },
  { code: 'nl', label: 'Nederlands', flag: '🇳🇱' },
  { code: 'es', label: 'Español', flag: '🇪🇸' },
  { code: 'bg', label: 'Български', flag: '🇧🇬' },
]

function LanguageSwitcher() {
  const { i18n } = useTranslation()

  return (
    <div className="flex flex-wrap gap-2 justify-center p-4">
      {languages.map(lang => (
        <button
          key={lang.code}
          onClick={() => i18n.changeLanguage(lang.code)}
          className={`text-xl px-4 py-3 rounded-xl border-2 font-semibold
            ${i18n.language === lang.code
              ? 'bg-blue-600 text-white border-blue-600'
              : 'bg-white text-gray-700 border-gray-300'
            }`}
        >
          {lang.flag} {lang.label}
        </button>
      ))}
    </div>
  )
}

export default LanguageSwitcher
Put this on the home screen or in a settings page. The selected language is remembered automatically between visits.

What You Get for Free
Browser auto-detects language on first visit (Dutch phone → Dutch UI)
User can override with the switcher
Choice is saved to localStorage automatically
Bulgarian Cyrillic script works with no extra setup — modern fonts support it
Hackathon Tip
Don't translate content inside the cards (the "5 scam warning signs" text etc.) — that takes hours. Just translate the navigation and button labels. That's enough to demo the feature convincingly. Say: "The UI adapts to your language, and content localization is on the roadmap."

plan.md
waht stands for mvp?
MVP = Minimum Viable Product

The smallest version of your app that still works and demonstrates the core idea. Just enough to be real, not everything you imagined.

For Ikigai: three buttons that open three screens with basic content = MVP. Live chat, real maps, backend = not MVP.

The point is to ship something that runs rather than build something perfect that isn't finished.