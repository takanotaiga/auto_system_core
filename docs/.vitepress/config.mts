import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  base: "/auto_system_core/",
  title: "Autosystem Core",
  description: "Documentation of the Autosystem Core",
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: 'Home', link: '/' },
      { text: 'API', link: '/api/api' },
      { text: 'Examples', link: '/example/markdown-examples' },
    ],

    sidebar: {
      "/example/": [
        {
          text: 'Examples',
          items: [
            { text: 'Markdown Examples', link: '/example/markdown-examples' },
            { text: 'Runtime API Examples', link: '/example/api-examples' }
          ]
        }
      ],
      "/api/": [
        {
          text: 'API Reference',
          items: [
            { text: 'API', link: '/api/api' },
            { text: 'API Backend', 
              items: [
                { text: 'Overview', link: '/api/api_backend' },
                { text: 'IPC', link: '/api/api_backend_ipc' }
              ] 
            }
          ]
        }
      ],
    },

    socialLinks: [
      { icon: 'github', link: 'https://github.com/vuejs/vitepress' }
    ]
  }
})
