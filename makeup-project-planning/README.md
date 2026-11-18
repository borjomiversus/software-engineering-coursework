# Software Project Management & Planning: MAKEUP Recommendation Engine

Project management documentation for developing an ML-powered recommendation engine for the **MAKEUP** e-commerce platform, covering SDLC selection, WBS/OBS decomposition, and RACI responsibility mapping.

---

## 1. Software Development Life Cycle (SDLC) Selection

* **Selected Model:** **Agile**
* **Justification:** E-commerce and Machine Learning (ML) requirements evolve rapidly based on user behavior and business metrics. Agile enables incremental feature delivery, rapid feedback loops from real users, iterative fine-tuning of recommendation algorithms, and close cross-functional collaboration among Business Analysts, ML Engineers, Developers, and QA specialists.

---

## 2. Work Breakdown Structure (WBS) & Organizational Breakdown Structure (OBS)

To manage the recommendation engine project effectively, a **Work Breakdown Structure (WBS)** and an **Organizational Breakdown Structure (OBS)** were designed and mapped via control accounts (intersections connecting specific work packages to responsible teams):

### WBS Hierarchy
1. **Management:**
   * `1.1` Project Plan & Backlog
   * `1.2` Risk Assessment
2. **Analysis:**
   * `2.1` Requirements Specification
   * `2.2` User Stories Creation
3. **Design (UX/ML):**
   * `3.1` UI/UX Prototyping
4. **Development:**
   * `4.1` ML Model Training
   * `4.2` Backend API Development
   * `4.3` Frontend Integration
5. **Testing:**
   * `5.1` Functional QA
   * `5.2` A/B Testing (CTR & Conversion)
6. **Release & Support:**
   * `6.1` Production Deployment
   * `6.2` Monitoring & Bugfixing

### OBS Teams & Roles
* **Analysis Team:** BA Lead, Senior BA, Junior BA
* **Design & ML:** UX/UI Designer, Data Scientist (ML)
* **Backend Team:** BE Team Lead, Senior BE Dev, Middle BE Dev, Junior BE Dev
* **Frontend Team:** FE Team Lead, Senior FE Dev, Middle FE Dev
* **QA Team:** QA Lead, Senior QA (Automation), Middle QA (Manual)
* **DevOps Team:** DevOps Lead, Senior DevOps, Middle DevOps

### WBS–OBS Control Account Diagram
<img width="1073" height="1280" alt="image" src="https://github.com/user-attachments/assets/f1a44c14-af56-4d87-8db7-2e19da4676b2" />


---

## 3. RACI Responsibility Matrix

### Legend
* **R (Responsible):** Executes the task.
* **A (Accountable):** Final owner accountable for task completion.
* **C (Consulted):** Provides input and expertise before execution.
* **I (Informed):** Updated on progress and outcomes after execution.

### Project Roles
* **PO** — Product Owner (represents business goals)
* **SM** — Scrum Master (facilitates Agile process and removes blockers)
* **BA** — Business Analyst (defines and details requirements)
* **UX/UI** — Designer (designs UI recommendation blocks)
* **ML** — Data Scientist (analyzes data and builds recommendation models)
* **BE Team** — Backend Developers (builds recommendation APIs)
* **FE Team** — Frontend Developers (integrates widgets into the storefront)
* **QA Team** — Quality Assurance (verifies accuracy and UI behavior)
* **DevOps** — DevOps Engineers (manages deployment and production stability)

### Matrix

| Task | PO | SM | BA | UX/UI | ML | BE Team | FE Team | QA Team | DevOps |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Define recommendation types ("Similar", "Frequently bought together") & KPIs (Conversion, AOV) | **A** | C | **R** | C | C | I | I | I | — |
| Analyze user & catalog data for algorithm selection | C | I | C | — | **R** | C | — | I | — |
| Design UI blocks for recommendations (product page, cart) | C | I | C | **R** | I | I | C | I | — |
| Create User Stories for initial recommendation MVP | **A** | C | **R** | C | I | I | I | I | — |
| Develop and train initial ML model | I | **A** | I | — | **R** | C | — | C | C |
| Develop API for serving recommendations | I | **A** | C | I | C | **R** | C | C | C |
| Integrate recommendation blocks into Frontend | I | **A** | C | C | I | C | **R** | C | — |
| Test recommendation accuracy & UI rendering | I | **A** | C | I | C | C | C | **R** | I |
| Configure A/B test to measure Conversion / AOV impact | **A** | C | I | C | C | I | **R** | **R** | C |
| Deploy v1.0 to Production | C | **A** | I | I | I | C | C | C | **R** |
| Monitor KPIs & system stability | **A** | **R** | I | I | C | C | I | I | **R** |
