<?hh // strict
namespace Fastuc\Db;

interface QueryListener
{
	/**
	 * @param string $query
	 */
	public function onPrepareQuery( string $query );
}

