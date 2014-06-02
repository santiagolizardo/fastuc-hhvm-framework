<?hh // strict
namespace Fastuc\Cache;

interface ICache
{
	/**
	 * @param string $key Key of the cached object
	 * @return mixed|null
	 */
	public function get( string $key ) : mixed;

	/**
	 * Adds (replaces) an object in the cache.
	 *
	 * @param string $key Key of the cached object.
	 * @param mixed $value Value to be cached.
	 */
	public function set( string $key, mixed $value ) : void;
}

