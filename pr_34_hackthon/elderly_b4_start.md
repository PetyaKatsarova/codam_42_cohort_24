How Hackathons Actually Work
You write all the code during the event. Judges look at:

Does it run live? (demo matters most)
Does it solve a real problem?
Is the idea good?
---------------------------------------------------
No one reviews your code quality. Ship something that works, not something that's perfect.

Do You Need a Database?
No. Not for 8 hours.

For this app, store everything in the browser with localStorage — it's built into every browser, zero setup:


// Save data
localStorage.setItem("familyPhone", "+31612345678")

// Read data
const phone = localStorage.getItem("familyPhone")

// Save an object
localStorage.setItem("user", JSON.stringify({ name: "Maria", streak: 5 }))
const user = JSON.parse(localStorage.getItem("user"))
That's your "database". It persists between page reloads. Good enough for a demo.

Only add a real DB if you need: accounts across devices, messaging between users, real-time data. Skip it unless Person D decides the chat feature needs it — and even then, use a free hosted service like Supabase (already has a UI, free tier, takes 15 min to set up).

Mobile vs Web — The Key Insight
There is no "mobile app language." The question is how it gets delivered:

Type	Language	How user opens it	        Needs app store?
Web app	JS/HTML/CSS	URL in browser	               No
PWA	JS/HTML/CSS	URL → "Add to home screen"	          No
React Native	JS (looks like web)	Downloaded from App Store	Yes
Native iOS	Swift	Downloaded from App Store	           Yes
Native Android	Kotlin/Java	Downloaded from App Store	Y     es
For a hackathon: build a PWA (Progressive Web App).

It's a web app that:

Opens in any browser on any device (phone, laptop, tablet)
Can be "installed" on the phone home screen (looks like a real app)
Works offline (optional)
Deploys in 2 minutes to a free URL
You write one codebase and it runs everywhere. No app store. Judges open a URL on their phone.

What Language / What You're Actually Writing
Since you know JS, you're good. The stack:


JavaScript (logic)
+ HTML (structure, but you barely write it raw)
+ CSS (styling, but Tailwind writes it for you)
+ React (library that makes building UI fast)
React is not a language — it's a JS library. You still write JavaScript. React just gives you reusable components (think: functions that return UI).

Without React (plain JS):


document.getElementById("btn").addEventListener("click", () => {
  document.getElementById("counter").textContent = count++
})
With React (same thing):


function Counter() {
  const [count, setCount] = React.useState(0)
  return <button onClick={() => setCount(count + 1)}>{count}</button>
}
React is just cleaner JS for UI. If you know JS, you can learn enough React in 2 hours to build this app.

Setup Tutorial (Do This Before the Hackathon)
Install Node.js first: nodejs.org — pick LTS version.

Then in terminal:


# Create the project
npm create vite@latest ikigai -- --template react
cd ikigai
npm install

# Add Tailwind CSS (for styling without writing CSS)
npm install -D tailwindcss postcss autoprefixer
npx tailwindcss init -p
Edit tailwind.config.js:


content: ["./index.html", "./src/**/*.{js,jsx}"],
Edit src/index.css — replace everything with:


@tailwind base;
@tailwind components;
@tailwind utilities;
Now run it:


npm run dev
Open http://localhost:5173 — you have a running app.

How React Works (15-minute mental model)
Everything is a component — a JS function that returns UI:


// src/components/BigButton.jsx
function BigButton({ label, onClick, color }) {
  return (
    <button
      onClick={onClick}
      className={`w-full p-6 text-2xl font-bold rounded-2xl text-white ${color}`}
    >
      {label}
    </button>
  )
}

export default BigButton
Use it anywhere:


import BigButton from "./components/BigButton"

<BigButton label="📱 How to Tech" color="bg-blue-600" onClick={() => navigate("/tech")} />
Pages = just components. Use React Router for navigation between them:


npm install react-router-dom

// src/App.jsx
import { BrowserRouter, Routes, Route } from "react-router-dom"
import Home from "./pages/Home"
import Health from "./pages/Health"
import Tech from "./pages/Tech"
import NotAlone from "./pages/NotAlone"

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/tech" element={<Tech />} />
        <Route path="/health" element={<Health />} />
        <Route path="/not-alone" element={<NotAlone />} />
      </Routes>
    </BrowserRouter>
  )
}
That's 90% of what you need to know. Four files, four pages.

Tailwind CSS in 5 Minutes
You don't write CSS files. You put classes directly on elements:


// Big blue button, full width, rounded corners, white text
<button className="w-full bg-blue-600 text-white text-2xl p-6 rounded-2xl">
  Click me
</button>

// Large readable text, dark color, centered
<p className="text-xl text-gray-800 text-center leading-relaxed">
  Hello Maria
</p>

// Vertical stack of items with gap between them
<div className="flex flex-col gap-4 p-6">
  ...
</div>
Classes like text-2xl, bg-blue-600, p-6 map to CSS. You learn them as you go — just Google "tailwind button" and copy.

Deploy to Vercel (Free, 2 Minutes)

npm install -g vercel
npm run build
vercel --prod
You get a URL like https://ikigai-demo.vercel.app. Share that link. Judges open it on their phone. Done.

Do You Present on a Laptop?
Both. Standard hackathon format:

Laptop for slides (2-3 slides max: problem, solution, demo)
Live demo is everything — open the URL, hand judges your phone, let them tap around
If you have a QR code on your slide → judges scan it → instant hands-on demo
The judges who try it themselves are 10x more impressed than judges who watch you use it.

Best Tips to Actually Win
1. Make a real elderly person use it during the hackathon.
Call your mom, grandparent, neighbor. Record a 30-second screen recording of them using it. Play that in your pitch. Nothing beats proof.

2. Nail the first 10 seconds of your demo.
Open the app, say "This is Maria, she's 74. She presses one button and her daughter knows she's okay today." Show that button working. Done.

3. Ship less, polish more.
Two features that work perfectly beat six features that are half-broken. Cut the chat feature if it's not ready. The check-in button working flawlessly is worth more.

4. The URL must work before you present.
Deploy by hour 6. Test the deployed version, not localhost. Vercel deployments behave slightly differently.

5. Make it actually big.
Open the app on your phone right now. If text feels small to you, it's unreadably small for a 75-year-old. Minimum text-xl (20px) for all body text, text-3xl for buttons.

How to Give It Away Free After
Day 1 after hackathon:

Keep it on Vercel (free forever for this scale)
Buy a domain: ikigai-app.com — costs €10/year on Namecheap
Get real users:

Post the link in local senior center Facebook groups
Print a simple A4 flyer with the QR code and leave it at a doctor's waiting room
Contact one local senior center and offer a free 30-min demo
No ongoing cost as long as you use localStorage (no server, no DB). The app just lives at a URL forever. That's the beauty of a PWA.