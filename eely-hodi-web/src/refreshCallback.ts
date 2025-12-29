let refreshCallback : () => void;

export function setRefreshCallback(cb : () => void) {
  refreshCallback = cb;
}

export function getRefreshCallback() : () => void {
  return refreshCallback;
}

export function doRefreshCallback() : void {
  refreshCallback();
}