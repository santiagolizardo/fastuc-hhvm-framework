<?hh
namespace Fastuc\Utils;

/**
 * The map class allows to access an array using primitive types setter/getters.
 */
class TypedArray
{
	/**
	 * @var array
	 */
	protected array $params;

	/**
	 * @param array $params
	 */
	public function __construct( array $params = array() )
	{
		$this->setParams( $params );
	}

	/**
	 * @param array $params
	 */
	public function setParams( array $params ) : void
	{
		$this->params = $params;
	}

	/**
	 * @param array $params
	 */
	public function addParams( array $params ) : void
	{
		$this->params = array_merge( $this->params, $params );
	}

	/**
	 * @return array
	 */
	public function getParams() : array
	{
		return $this->params;
	}

	/**
	 * @param string $name
	 * @return bool
	 */
	public function hasParam( string $name ) : bool
	{
		return isset( $this->params[ $name ] );
	}

	/**
	 * @param string $name
	 * @return mixed
	 */
	public function getParam( string $name ) : mixed
	{
		return $this->hasParam( $name ) ? $this->params[ $name ] : null;
	}

	/**
	 * @param string $name
	 * @param mixed $value
	 */
	public function setParam( string $name, mixed $value ) : void
	{
		$this->params[ $name ] = $value;
	}

	/**
	 * @param string $name
	 */
	public function unsetParam( string $name ) : void
	{
		unset( $this->params[ $name ] );
	}

	/**
	 * Resets the internal array removing all elements.
	 */
	public function unsetParams() : void
	{
		$this->params = array();
	}

	/**
	 * @param string $name
	 * @param mixed $value
	 */
	public function setString( string $name, mixed $value ) : void
	{
		$this->setParam( $name, strval( $value ) );
	}

	/**ranges - but still looking £40k+
	 * Have attahced a slightly more detailed CV to his jobvite
	 *
	 * Is it worth telephone interviewing at that level?
	 * May 14 at 3:18 pm
	 *
	 *
	 * @param string $name
	 * @param string $default Default value if the parameter does not exist.
	 * @return string
	 */
	public function getString( string $name, $default = null ) : string
	{
		$value = $this->getParam( $name );
		return null === $value ? $default : strval( $value );
	}

	/**
	 * @param string $name
	 * @param integer $default Default value if the parameter does not exist.
	 * @return integer
	 */
	public function getInt( string $name, $default = null ) : int
	{
		$value = $this->getParam( $name );
		return null === $value ? $default : intval( $value );
	}

	/**
	 * @param string $name
	 * @param integer $value
	 */
	public function setInt( string $name, $value ) : void
	{
		$this->setParam( $name, intval( $value ) );
	}

	/**
	 * @param string $name
	 * @param float $default Default value if the parameter does not exist.
	 * @return float
	 */
	public function getFloat( string $name, $default = null ) : float
	{
		$value = $this->getParam( $name );
		return null === $value ? $default : floatval( $value );
	}

	/**
	 * @param string $name
	 * @param bool $default Default value if the parameter does not exist.
	 * @return bool
	 */
	public function getBoolean( string $name, $default = false ) : bool
	{
		$value = $this->getParam( $name );
		return null === $value ? $default : (bool)( $value );
	}

	/**
	 * @param string $name
	 * @return array
	 */
	public function getArray( string $name ) : array
	{
		$value = $this->getParam( $name );

		if( null === $value )
			return array();

		if( !is_array( $value ) )
			return null;

		return $value;
	}
}

