<?hh // strict
namespace Fastuc\Db;

class Connection extends \mysqli
{
	/**
	 * @var array
	 */
	private array $queryListeners;

	/**
	 * @param string $host
	 * @param string $user
	 * @param string $pass
	 * @param string $name
	 */
	public function __construct( string $host, string $user, string $pass, string $name )
	{
		@parent::__construct( $host, $user, $pass, $name );

		if( $this->connect_error )
		{
			throw new \Fastuc\Db\Exception( $this->connect_error );
		}

		$this->set_charset( 'utf8' );

		$this->queryListeners = array();
	}

	public function prepare( string $query ) : \mysqli_stmt
	{
		foreach( $this->queryListeners as $queryListener )
		{
			$queryListener->onPrepareQuery( $query );
		}

		return parent::prepare( $query );
	}

	public function addQueryListener( QueryListener $queryListener ) : void
	{
		$this->queryListeners[] = $queryListener;
	}
}

