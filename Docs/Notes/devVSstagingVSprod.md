# Environment Differences

## Dev (safe & fast iteration)
- **Players**: internal only (you + team test accounts).
- **Data**: throwaway; can be wiped/reset anytime.
- **Queues/Matchmaking**: `QuickMatch_Dev`; fewer checks, bots allowed.
- **Auth**: guest/custom IDs OK; Apple Sign-In optional.
- **Economy**: cheap prices, free grants, debug unlocks.
- **IAP**: sandbox fakes or test products; server validation can be relaxed.
- **Analytics**: verbose logs; sample 100%; noisy events fine.
- **Builds**: debug/dev builds; cheats & debug menus enabled.
- **Stability**: okay to break; hotfix constantly.

---

## Staging (production-like)
- **Players**: internal + limited external testers (e.g., TestFlight internal/external).
- **Data**: persistent; schema and migrations tested here first.
- **Queues/Matchmaking**: `QuickMatch_Staging`; same rules as Prod.
- **Auth**: real Apple Sign-In; identity flows match Prod.
- **Economy**: real prices/SKUs in sandbox; **no** free debug grants.
- **IAP**: full purchase → receipt → server validation → entitlement.
- **Analytics**: same event schema/sample rate as Prod; dashboards should read cleanly.
- **Builds**: release candidates (shipping config), no cheats, feature flags via RC/Title Data.
- **Stability**: must be stable; only cherry-picked changes.

---

## Prod (live environment)
- **Players**: all real users.
- **Data**: permanent, production database; never wiped casually.
- **Queues/Matchmaking**: `QuickMatch_Prod`; tuned rules, no shortcuts.
- **Auth**: only real Apple/Google accounts; strict identity checks.
- **Economy**: live prices, currencies, cosmetics; no free grants outside promotions.
- **IAP**: real purchases → server validation mandatory → grants tied to entitlements.
- **Analytics**: clean dashboards; only production-quality events.
- **Builds**: App Store / Play Store release builds only.
- **Stability**: critical; monitored with alerts; downtime requires incident response.

---

## Easy Rule of Thumb
- **Dev**: move fast, experiment, break things.
- **Staging**: production rehearsal, QA + external test.
- **Prod**: real players, money, and metrics — must not break.

---

## Promotion Flow
`Dev` → (feature complete) → **merge to Staging** → QA & validation  
`Staging` → verified stable → **promote to Prod**
